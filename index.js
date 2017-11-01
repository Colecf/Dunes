var cheerio = require('cheerio');
var request = require('sync-request');
var fs = require('fs');


var stack = [];
const output_script = "dunes.csv";
if(fs.existsSync(output_script)){
	fs.truncateSync(output_script, 0);
}

function top(){
	return stack[stack.length-1];
}

function pop(){
	if(stack.length < 0){
		console.error("Popping with empty stack");
	}
	return stack.pop();
}

function get_page(url){
	if(stack.length > 0){
		pop();
	}	stack.push(request('GET', url).getBody());
}

function children(query, css){
	var $ = query;
	var html = "";
	$(css).contents().each(function(i, elem){
		html += $.html(this);
	});
	return html;
}

function select_by_css(html, css, get_children=false){
	var $ = cheerio.load(html);
	pop();
	if(get_children){
		stack.push(children($, css));
	}
	else{
		stack.push($.html(css));
	}
}
function get_text(html){
	var $ = cheerio.load(html);
	pop();
	var ret = $(html).first().text();
	stack.push(ret);
}

function add_row(){
	var data = fs.readFileSync(output_script);
	fs.truncateSync(output_script, data.length-1);
	fs.appendFileSync(output_script, '\n');
}

function add_column(data){
	fs.appendFileSync(output_script, '"' + data.replace(/"/g, '""') + '",');
}

function scope(){
	stack.push(top());
}

function constant(data){
	if(stack.length > 0){
		pop();
	}
	stack.push(data);
}

function attribute(attribute){
	var $ = cheerio.load(pop());
	stack.push($("*").first().attr(attribute));
}

function next(){
	var $ = cheerio.load(top());
	pop();
	var html = "";
	$("*").first().nextAll().each(function(i, elem){
		html += $.html(this);
	});
	stack.push(html);
}

constant("https://www.basketball-reference.com/leagues/NBA_1980.html")
get_page(top());
select_by_css(top(), "#divs_standings_E");
select_by_css(top(), "tr.full_table", true);
scope();
constant("team");
add_column(top());
constant("wins");
add_column(top());
constant("losses");
add_column(top());
constant("W/L%");
add_column(top());
constant("GB");
add_column(top());
constant("PS/G");
add_column(top());
constant("PA/G");
add_column(top());
constant("SRS");
add_column(top());
add_row();
pop();
while(top() != ""){
	scope();
	get_text(top());
	add_column(top());
	pop();
	scope();
	attribute("data-stat")
	if(top() === "srs"){
		add_row();
	}
	pop();
	next();
}



// Diagram:
// DL first team
// Scope
// 	constant year
// 	add col
// 	constant team
// 	add col
// 	add row
// Scope
// 	select year css
// 	get text
// 	add col
// Scope
// 	select team css
// 	get text
// 	add col
// 	add row
// DL 2nd team
// Scope
// 	select year css
// 	get text
// 	add col
// Scope
// 	select team css
// 	get text
// 	add col
// 	add row

// Example output:
// constant("https://www.basketball-reference.com/teams/SAS/1980.html")
// get_page(top());
// scope();
// constant("year");
// add_column(top());
// constant("team");
// add_column(top());
// add_row();
// pop();
// scope();
// select_by_css(top(), "h1[itemprop='name'] span:nth-child(1)");
// get_text(top());
// add_column(top());
// pop();
// select_by_css(top(), "h1[itemprop='name'] span:nth-child(2)");
// get_text(top());
// add_column(top());
// add_row();
// pop();
// constant('https://www.basketball-reference.com/teams/LAL/1980.html');
// get_page(top());
// scope();
// select_by_css(top(), "h1[itemprop='name'] span:nth-child(1)");
// get_text(top());
// add_column(top());
// pop();
// select_by_css(top(), "h1[itemprop='name'] span:nth-child(2)");
// get_text(top());
// add_column(top());
// add_row();
// pop();