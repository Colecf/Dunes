var cheerio = require('cheerio');
var request = require('request');
var rp = require('request-promise');
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
	return rp(url)
		.then(function(body){
			if(stack.length > 0){
				pop();
			}
			stack.push(body);
			return body;
		})
		.catch(function(err){
			console.error("get request failed: ", err);
		});
}

function select_by_css(html, css){
	var $ = cheerio.load(html);
	pop();
	var ret = $.html(css);
	stack.push(ret);
	return ret;
}

function get_text(html){
	var $ = cheerio.load(html);
	pop();
	var ret = $(html).text();
	stack.push(ret);
	return ret;
}

function add_row(){
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
get_page('https://www.basketball-reference.com/teams/SAS/1980.html')
	.then(function(){
		scope();
	})
	.then(function(){
		constant("year");
	})
	.then(function(){
		add_column(top());
	})
	.then(function(){
		constant("team");
	})
	.then(function(){
		add_column(top());
	})
	.then(function(){
		add_row();
	})
	.then(function(){
		pop();
	})
	.then(function(){
		scope();
	})
	.then(function(){
		return select_by_css(top(), "h1[itemprop='name'] span:nth-child(1)");
	})
	.then(function(res){
		return get_text(top());
	})
	.then(function(res){
		add_column(top());
	})
	.then(function(){
		pop();
	})
	.then(function(){
		return select_by_css(top(), "h1[itemprop='name'] span:nth-child(2)");
	})
	.then(function(){
		return get_text(top());
	})
	.then(function(){
		add_column(top());
	})
	.then(function(){
		add_row();
	})
	.then(function(){
		pop();
	})
	.then(function(){
		return get_page('https://www.basketball-reference.com/teams/LAL/1980.html')
	})
	.then(function(){
		scope();
	})
	.then(function(){
		return select_by_css(top(), "h1[itemprop='name'] span:nth-child(1)");
	})
	.then(function(res){
		return get_text(top());
	})
	.then(function(res){
		add_column(top());
	})
	.then(function(){
		pop();
	})
	.then(function(){
		return select_by_css(top(), "h1[itemprop='name'] span:nth-child(2)");
	})
	.then(function(){
		return get_text(top());
	})
	.then(function(){
		add_column(top());
	})
	.then(function(){
		add_row();
	})
	.then(function(){
		pop();
	})