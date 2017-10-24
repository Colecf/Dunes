var cheerio = require('cheerio');
var request = require('request');
var rp = require('request-promise');


var stack = [];

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
	var ret = $(css).html();
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



get_page('https://www.basketball-reference.com/teams/SAS/1980.html')
	.then(function(body){
		return select_by_css(body, "h1[itemprop='name']");
	})
	.then(function(res){
		return get_text(res);
	})
	.then(function(res){
		console.log(res);
	})
	.then(function(res){
		get_page('https://www.basketball-reference.com/teams/LAL/1980.html').then(function(res){
			return select_by_css(res, "h1[itemprop='name']");
	})
	.then(function(res){
		return get_text(res);
	})
	.then(function(res){
		console.log(res);
	})
})