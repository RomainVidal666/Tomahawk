<html class=""><head>
	 <meta charset="ISO-8859-1"> 
		<title>Tomahawk site 2</title>
		<link rel="stylesheet" href="design.css">
		<link rel="stylesheet" type="text/css" href="css/component.css">
		<link rel="stylesheet" type="text/css" href="css/normalize.css">
		<link rel="stylesheet" type="text/css" href="css/demo.css">
		<script src="https://code.jquery.com/jquery-1.10.2.js"></script>
		<script src="js/snap.svg-min.js"></script>
		<!-- BOOTSTRAP - Latest compiled and minified CSS -->
		<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/css/bootstrap.min.css" integrity="sha384-1q8mTJOASx8j1Au+a5WDVnPi2lkFfwwEAa8hDDdjZlpLegxhjVME1fgjWPGmkzs7" crossorigin="anonymous">

		<!-- Optional theme -->
		<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/css/bootstrap-theme.min.css" integrity="sha384-fLW2N01lMqjakBkx3l/M9EahuwpSfeNvV63J5ezn3uZzapT0u7EYsXMjQV+0En5r" crossorigin="anonymous">

		<!-- Latest compiled and minified JavaScript -->
		<script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/js/bootstrap.min.js" integrity="sha384-0mSbJDEHialfmuBBQP6A4Qrprq5OVfW37PRR3j5ELqxss1yVqOtnepnHVP9aJ7xS" crossorigin="anonymous"></script>



		<script>

		$( document ).ready(function() {
				var video = document.querySelector('video')
				, container = document.querySelector('#fond_video');

				var setVideoDimensions = function () {
					// Video's intrinsic dimensions
					var w = video.videoWidth
					, h = video.videoHeight;

					// Intrinsic Ratio
					// Will be more than 1 if W > H and less if W < H
					var videoRatio = (w / h).toFixed(2);

					// Get the container's computed styles
					//
					// Also calculate the min dimensions required (this will be
					// the container dimentions)
					var containerStyles = window.getComputedStyle(container)
					, minW = parseInt( containerStyles.getPropertyValue('width') )
					, minH = parseInt( containerStyles.getPropertyValue('height') );

					// What's the min:intrinsic dimensions
					//
					// The idea is to get which of the container dimension
					// has a higher value when compared with the equivalents
					// of the video. Imagine a 1200x700 container and
					// 1000x500 video. Then in order to find the right balance
					// and do minimum scaling, we have to find the dimension
					// with higher ratio.
					//
					// Ex: 1200/1000 = 1.2 and 700/500 = 1.4 - So it is best to
					// scale 500 to 700 and then calculate what should be the
					// right width. If we scale 1000 to 1200 then the height
					// will become 600 proportionately.
					var widthRatio = minW / w
						, heightRatio = minH / h;

					// Whichever ratio is more, the scaling
					// has to be done over that dimension
					if (widthRatio > heightRatio) {
						var newWidth = minW;
						var newHeight = Math.ceil( newWidth / videoRatio );
					}
					else {
						var newHeight = minH;
						var newWidth = Math.ceil( newHeight * videoRatio );
					}

					video.style.width = newWidth + 'px';
					video.style.height = newHeight + 'px';
				};

				video.addEventListener('loadedmetadata', setVideoDimensions, false);
				window.addEventListener('resize', setVideoDimensions, false);
		});

		</script>
	</head>
	<body>
		<!-- NAVBAR -->
		<nav class="navbar navbar-default navbar-top">
			<div class="container">
			<div class="navbar-header">
			
			<button type="button" class="navbar-toggle collapsed" data-toggle="collapse" data-target="#navbar" aria-expanded="false" aria-controls="navbar">
			<span class="sr-only">Toggle navigation</span>
			<span class="icon-bar"></span>
			<span class="icon-bar"></span>
			<span class="icon-bar"></span>
			</button><a style="" class="navbar-brand" href="index.html">Tomahawk</a>
			</div>
			<div id="navbar" class="navbar-collapse collapse">
			<ul class="nav navbar-nav">
			<li><a href="index.html">Dons</a></li>
			<li class="active"><a href="#">Dons</a></li>
			<li><a href="exemples.html">Dons</a></li>

			</ul>
			<ul class="nav navbar-nav navbar-right">
			<li><a href="a_propos.html">Dons</a></li>


			</ul>
			</div><!--/.nav-collapse -->
			</div>
		</nav>

		<!-- VIDEO -->
		<div id="fond_video" class="fullscreen-bg">
			<video style="width: 1353px; height: 761px; z-index: -50;" autoplay="" loop="" class="fullscreen-bg__video">
			<source src="./video/chat_mendiant.mp4" type="video/mp4">
			</video>
		</div>

		<!-- CONTAINER -->		
		<div class="container-fluid">

		<div class="row">
		<div class="col-md-4" style="color: white;">
			<div style="margin: 40px;" class="description">		
				<?php phpinfo (); ?>
			</div>
		</div>
		<div class="col-md-4" style="color: white;"></div>
		<div class="col-md-4">
		<form action="dons_trait.php" method="post" class="bootstrap-frm">
		<h1>Faire un don<span>Merci de remplir les champs ci-dessous.</span></h1>
		<p><label><span>Nom complet :</span>
		<input id="name" name="name" placeholder="Nom Prenom" type="text"></label>
		<label><span>Numero de carte</span>
		<input id="card_number" name="card_number" placeholder="Numero de carte" type="text"></label>
		<label><span>Cryptogramme :</span>
		<input id="cryptogramm" name="cryptogramm" placeholder="Cryptogramme" type="text"></label>
		<label><span>&nbsp;</span>
		<input class="button" value="Send" type="submit"></label></p>
		</form>
		</div>
		</div>
		</div>
	

</body></html>
