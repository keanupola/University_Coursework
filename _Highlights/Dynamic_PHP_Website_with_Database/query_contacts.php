<?php
include("functions.php");
$dblink=db_connect("contact_data");
$sql="Select * from `contact_info`";
$results=$dblink->query($sql) or
	die("Something went wrong with $sql".$dblink->error);

while ($data=$results->fetch_array(MYSQLI_ASSOC))
{
	echo '<tr>';
	echo '<td>'.$data['first_name'].'</td>';
	echo '<td>'.$data['last_name'].'</td>';
	echo '<td>'.$data['email'].'</td>';
	echo '<td>'.$data['phone'].'</td>';
	echo '<td>'.$data['comments'].'</td>';
	echo '</tr>';
	
}
?>