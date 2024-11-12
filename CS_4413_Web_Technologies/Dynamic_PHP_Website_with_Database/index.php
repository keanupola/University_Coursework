<?php
session_start();
include("functions.php");
?>

<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Welcome to Keanu Anderson-Pola's Website</title>
    <link rel="stylesheet" href="assets/css/normalize.css">
    <link rel="stylesheet" href="assets/css/bootstrap.css">
    <link rel="stylesheet" href="assets/css/style-portfolio.css">
    <link rel="stylesheet" href="assets/css/picto-foundry-food.css" />
    <link rel="stylesheet" href="assets/css/jquery-ui.css">
    <link href="assets/css/font-awesome.min.css" rel="stylesheet">
	<link rel="stylesheet" href="assets/css/main.css" media="screen" type="text/css">
    <link rel="icon" href="assets/favicon-1.ico" type="image/x-icon">
	
</head>
<body>
	<nav class="navbar navbar-default navbar-fixed-top" role="navigation">
    <div class="container">
        <div class="navbar-header">
            <button type="button" class="navbar-toggle collapsed" data-toggle="collapse" data-target="#bs-example-navbar-collapse-1">
                <span class="sr-only">Toggle navigation</span>
                <span class="icon-bar"></span>
                <span class="icon-bar"></span>
                <span class="icon-bar"></span>
            </button>
			
            <a class="navbar-brand" href="#home">Keanu Anderson-Pola's Website</a>
			
        </div>
		
		<!-- Menu Items -->
		<?php
			include("navigation.php");
		?>
		
    </div>
</nav>
	
<?php
	if (!isset($_GET['page']))
		$page="home";
	else
		$page=$_GET['page'];
	
	switch($page){
		case "education":
			include("education.php");
			break;
		case "hobbies and interests":
			include("hobbies.php");
			break;
		case "professional aspirations":
			include("aspirations.php");
			break;
		case "favorite movies":
			include("movies.php");
			break;
		case "dogs":
			include("page.php");
			break;
		case "contact":
			include("contact.php");
			break;
		case "results":
			include("results.php");
			break;
		case "register":
			include("register.php");
			break;
		case "login":
			include("login.php");
			break;
		default:
			include("home.php");
			break;
	};
?>
	
<!-- Footer -->
<footer class="sub_footer">
    <div class="container">
        <!-- TODO: add footer info -->
    </div>
</footer>
	
	<script src="assets/js/add-content.js"></script>
</body>
</html>
