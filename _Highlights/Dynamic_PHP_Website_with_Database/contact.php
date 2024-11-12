<?php
if (session_status() == PHP_SESSION_NONE) {
    session_start();
}
?>

<section class="description_content">
    <div class="text-content container">
        <div class="col-md-12">
            <?php
            $errors = "";

            if (isset($_POST['submit'])) {
                // Processing form data after submission
                $firstname = $_POST['firstname'];
                $lastname = $_POST['lastname'];
                $email = $_POST['email'];
                $phone = $_POST['phone'];
                $username = $_POST['username'];
                $password = $_POST['password'];
                $comments = addslashes($_POST['comments']);

                if (empty($firstname) || !preg_match("/^[a-zA-Z'-]+$/", $firstname)) {
                    $errors .= 'firstNameNull;';
                } else {
                    $_SESSION['firstname'] = $firstname;
                }
				
				// Validate Last Name
                if (empty($lastname) || !preg_match("/^[a-zA-Z'-]+$/", $lastname)) {
                    $errors .= 'lastNameNull;';
                } else {
                    $_SESSION['lastname'] = $lastname;
                }

                // Validate Email
                if (empty($email) || !filter_var($email, FILTER_VALIDATE_EMAIL)) {
                    $errors .= 'emailInvalid;';
                } else {
                    $_SESSION['email'] = $email;
                }

                // Validate Phone Number
                if (empty($phone) || !preg_match("/^\d+$/", $phone)) {
                    $errors .= 'phoneInvalid;';
                } else {
                    $_SESSION['phone'] = $phone;
                }
				
				// Validate username
                if (empty($username)) {
                    $errors .= 'userNameNull;';
                } else {
                  $_SESSION['username'] = $username;
                }

                // Validate password
                if (empty($password)) {
                    $errors .= 'passwordNull;';
                } else {
                  $_SESSION['password'] = $password;
                }

                // Validate comments
                if (empty($comments)) {
                    $errors .= 'commentsNull;';
                } else {
                  $_SESSION['comments'] = $comments;
                }

                if (!empty($errors)) {
                    header("Location: index.php?page=contact&errMsg=$errors");
                    exit;
                }
            }

            if (!isset($_POST['submit'])) {
                // Display the form
				echo '<div id="contact">';
				echo '<div class="row">';
				echo '<div class="col-md-6">';
				echo '<form method="post" action="" id="mainForm" style="padding:20px;margin:20px">';

				// Function to generate each field with error handling
				function displayField($name, $label, $errorKey, $type = 'text') {
					$value = $_SESSION[$name] ?? ''; // isset shorthand
					$errorClass = '';
					$errorMessage = '';
					if (isset($_GET['errMsg']) && strstr($_GET['errMsg'], $errorKey)) {
						$errorClass = 'has-error';
						switch ($errorKey) {
							case 'firstNameNull':
								$errorMessage = 'First name cannot be blank!';
								break;
							case 'lastNameNull':
								$errorMessage = 'Last name cannot be blank!';
								break;
							case 'emailInvalid':
								$errorMessage = 'Invalid email format!';
								break;
							case 'phoneInvalid':
								$errorMessage = 'Phone number should only contain digits!';
								break;
							case 'userNameNull':
								$errorMessage = 'Username cannot be blank!';
								break;
							case 'passwordNull':
								$errorMessage = 'Password cannot be blank!';
								break;
							case 'commentsNull':
								$errorMessage = 'Comments cannot be blank!';
								break;
						}
					}

					echo "<div class='form-group $errorClass'>";
					echo "<label for='$name'>$label:</label>";
					echo "<input type='$type' name='$name' class='form-control' id='$name' value='$value'>";
					if (!empty($errorMessage)) {
						echo "<div class='help-block'>$errorMessage</div>";
					}
					echo "</div>";
				}

				// Generate fields
				displayField('firstname', 'First Name', 'firstNameNull');
				displayField('lastname', 'Last Name', 'lastNameNull');
				displayField('email', 'Email', 'emailInvalid', 'email');
				displayField('phone', 'Phone Number', 'phoneInvalid', 'tel');
				displayField('username', 'Username', 'userNameNull');
				displayField('password', 'Password', 'passwordNull', 'password');
				displayField('comments', 'Comments', 'commentsNull', 'textarea');

				echo '<button type="submit" name="submit" class="btn btn-default">Submit</button>';
				echo '</form>';
				echo '</div>'; // col-md-6
				echo '</div>'; // row
				echo '</div>'; // contact

            } else {
                $dblink=db_connect("contact_data");
				$sql="Insert into `contact_info` (`first_name`,`last_name`,`email`,`phone`,`username`,`password`,`comments`) values
				('$firstname','$lastname','$email','$phone','$username','$password','$comments')";
				$dblink->query($sql) or
					die("<h2>Something went wrong with: $sql<br>".$dblink->error.'</h2>');
				echo '<br><h2>Your data has been saved successfully.</h2>';
				
            }
            ?>
        </div>
    </div>
</section>

<script src="assets/js/formValidation.js"></script>