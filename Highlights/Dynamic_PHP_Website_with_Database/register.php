<?php
echo '<section id="home">';
if (!isset($_POST['submit']))
{
    $errorMessage = '';
    // Display error message if the username already exists
    if (isset($_GET['error']) && $_GET['error'] == 'usernameExists') {
        $errorMessage = '<p style="color: red;">Username already exists. Please choose another username.</p>';
    }

    echo '<br><br><br><br><br><br><br><br>';
    echo $errorMessage;
    echo '<h2 style="text-align: center;">Please fill out the following to create an account.</h2>';
    echo '<form method="post" action="" id="mainForm" style="padding:20px;margin:20px;">';
    echo '<div class="form-group">';
    echo '<label class="control-label" for="username">Username: </label>';
    echo '<input type="text" id="username" name="username" class="form-control" required>';
    echo '</div>';
    
    echo '<div class="form-group">';
    echo '<label class="control-label" for="password">Password: </label>';
    echo '<input type="password" id="password" name="password" class="form-control" required>';
    echo '</div>';
    
    echo '<div class="form-group">';
    echo '<button class="btn btn-primary" type="submit" value="submit" name="submit">Submit</button>';
    echo '</div>';
    echo '</form>';
}

if (isset($_POST['submit'])) {
    $username = addslashes($_POST['username']);
    $passText = $_POST['password'];
    $salt = "WEBTECHSPRING2024";
    $dblink = db_connect("user_data");

    // Check if username already exists
    $checkSql = "Select * from `accounts` where `username` = '$username'";
    $result = $dblink->query($checkSql);

    if ($result->num_rows > 0) {
        // If username exists, redirect to register page with error
        header("Location: index.php?page=register&error=usernameExists");
        exit;
    } else {
        // If username does not exist, add new user
        $password = hash('sha256', $salt.$passText.$username);
        $sql = "Insert into `accounts` (`username`, `auth_hash`) values ('$username', '$password')";
        $dblink->query($sql) or die("Something went wrong with the SQL query<br>" . $dblink->error);

        // Redirect to login page after successful registration
        header("Location: index.php?page=login&success=1");
        exit;
    }
}

echo '</section>';
?>
<script src="assets/js/formValidation.js"></script>
