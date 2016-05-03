$(function () {
	var speed = 200;
	$("a").fadeTo ( speed, 0, function next () {
  		$(this).fadeTo ( speed, 1 ).fadeTo ( speed, 0, next );
	});

});