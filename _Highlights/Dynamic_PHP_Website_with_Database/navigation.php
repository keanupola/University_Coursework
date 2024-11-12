<?php
echo '<div class="collapse navbar-collapse" id="bs-example-navbar-collapse-1">';
echo '<ul class="nav navbar-nav main-nav clear navbar-right">';
if(!isset($_GET['page']))
	$page="home";
else
	$page=$_GET['page'];

if ($page=="home")
	echo '<li><a class="color_animation active" href="index.php">HOME</a></li>';
else
	echo '<li><a class="color_animation" href="index.php">HOME</a></li>';
	
if ($page=="education")
	echo '<li><a class="color_animation active" href="index.php?page=education">EDUCATION</a></li>';
else
	echo '<li><a class="color_animation" href="index.php?page=education">EDUCATION</a></li>';
	
if ($page=="hobbies and interests")
	echo '<li><a class="color_animation active" href="index.php?page=hobbies and interests">HOBBIES AND INTERESTS</a></li>';
else
	echo '<li><a class="color_animation" href="index.php?page=hobbies and interests">HOBBIES AND INTERESTS</a></li>';
	
if ($page=="professional aspirations")
	echo '<li><a class="color_animation active" href="index.php?page=professional aspirations">PROFESSIONAL ASPIRATIONS</a></li>';
else
	echo '<li><a class="color_animation" href="index.php?page=professional aspirations">PROFESSIONAL ASPIRATIONS</a></li>';

if ($page=="favorite movies")
	echo '<li><a class="color_animation active" href="index.php?page=favorite movies">FAVORITE MOVIES</a></li>';
else
	echo '<li><a class="color_animation" href="index.php?page=favorite movies">FAVORITE MOVIES</a></li>';

if ($page=="contact")
	echo '<li><a class="color_animation active" href="index.php?page=contact">CONTACT</a></li>';
else
	echo '<li><a class="color_animation" href="index.php?page=contact">CONTACT</a></li>';

if ($page == "results")
    echo '<li><a class="color_animation active" href="index.php?page=results">RESULTS</a></li>';
else
    echo '<li><a class="color_animation" href="index.php?page=results">RESULTS</a></li>';

if ($page == "login")
    echo '<li><a class="color_animation active" href="index.php?page=login">LOGIN</a></li>';
else
    echo '<li><a class="color_animation" href="index.php?page=login">LOGIN</a></li>';

echo '</ul>';
echo '</div>';
?>