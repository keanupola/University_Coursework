<?php
echo '<section id="home">';
if (!isset($_POST['submit'])) {
	echo '<br><br><br><br><br><br><br><br>';
    // Display success message if registration was successful
    if (isset($_GET['success']) && $_GET['success'] == '1') {
        echo '<p style="color: green;">Registration successful. Please log in.</p>';
    }

    // Display error messages
    if (isset($_GET['error'])) {
        switch ($_GET['error']) {
            case 'loginFailed':
                echo '<p style="color: red;">Invalid username or password. Please try again.</p>';
                break;
            case 'emptyFields':
                echo '<p style="color: red;">Please fill in all fields.</p>';
                break;
        }
    }

    echo '<h2 style="text-align: center;">Please enter your login credentials</h2>';
    echo '<form method="post" action="" id="mainForm" style="padding:20px;margin:20px;">';
    echo '<div class="form-group">';
    echo '<label class="control-label" for="username">Username: </label>';
    echo '<input type="text" id="username" name="username" class="form-control">';
    echo '</div>';
    echo '<div class="form-group">';
    echo '<label class="control-label" for="password">Password: </label>';
    echo '<input type="password" id="password" name="password" class="form-control">';
    echo '</div>';
    echo '<div class="form-group">';
    echo '<button class="btn btn-primary" type="submit" name="submit" value="submit">Submit</button>';
    echo '</div>';
    echo '</form>';
} else {
    $username = addslashes($_POST['username']);
    $passText = $_POST['password'];

    // Ensure fields are not empty
    if (empty($username) || empty($passText)) {
        header("Location: index.php?page=login&error=emptyFields");
        exit;
    }

    $salt="WEBTECHSPRING2024";
    $dblink=db_connect("user_data");
    $password=hash('sha256', $salt.$passText.$username);
    $sql="Select `auto_id` from `accounts` where `auth_hash`='$password'";
    $result=$dblink->query($sql) or
		die("Something went wrong with $sql<br>".$dblink->error);
    if ($result->num_rows > 0) {
        $salt = microtime();
        $sid = hash('sha256', $salt.$password);
        $sql = "Update `accounts` set `session_id`='$sid' where `auth_hash`='$password'";
        $dblink->query($sql) or die("Error updating session ID: " . $dblink->error);
        redirect("index.php?page=results&sid=$sid");
    } else {
        header("Location: index.php?page=login&error=loginFailed");
        exit;
    }
}
echo '</section>';
?>
<script src="assets/js/formValidation.js"></script>
