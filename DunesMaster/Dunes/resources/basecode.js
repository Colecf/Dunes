var cheerio=require('cheerio');
var request=require('sync-request');
var fs=require('fs');
var stack=[];
function top() {
    return stack[stack.length-1];
}
function pop() {
    if(stack.length<0){
        console.error('Popping with empty stack');
    }
    return stack.pop()
}
function get_page(url) {
    if(stack.length>0)
    {
        pop()
    }
    stack.push(request('GET',url).getBody())
}
function children(query,css){
    var $=query;
    var html="";
    $(css).contents().each(function(i,elem){
        html+=$.html(this);
    });
    return html;
}
function select_by_css(html,css,get_children=false){
    var $=cheerio.load(html);
    pop();
    if(get_children){
        stack.push(children($,css));
    }else{
        stack.push($.html(css));
    }
}
function get_text(){
    var $=cheerio.load(top());
    pop();
    var ret=$("*").first().text();
    stack.push(ret);
}
function add_row(){
    var data=fs.readFileSync(output_script);
    fs.truncateSync(output_script,data.length-1);
    fs.appendFileSync(output_script,'\\n');
}
function add_column(data){
    fs.appendFileSync(output_script,'"'+data.replace(/\"/g,'""')+'",');
}
function scope(){
    stack.push(top());
}
function constant(data){
    if(stack.length>0){
        pop();
    }
    stack.push(data);
}
function attribute(attribute){
    var $=cheerio.load(pop());
    stack.push($("*").first().attr(attribute));
}
function next(){
    var $=cheerio.load(top());
    pop();
    var html="";
    $("*").first().nextAll().each(function(i,elem){
        html+=$.html(this);
    });
    stack.push(html);
}
