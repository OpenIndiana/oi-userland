var i = new Image();
var d = new Date();
var uri = "http://pkg.oracle.com/6p.png" + "?time=" + d.getTime();
var t;

i.onload = function() {
	clearTimeout(t);
	t = null;
};

var fail = function () {
	clearTimeout(t);
	t = null;
	i = null;
}

i.src = uri;
t = setTimeout("fail()", 30000);
