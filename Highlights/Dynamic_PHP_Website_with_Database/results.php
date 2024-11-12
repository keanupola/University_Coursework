<!-- Include jquery scripts -->
<script src ="assets/js/jquery-3.5.1.js"></script>
<?php
if (isset($_REQUEST['sid']) && $_REQUEST['sid']!="")
	{
	$dblink=db_connect("user_data");
	$sid=addslashes($_REQUEST['sid']);
	$sql="Select `auto_id` from `accounts` where `session_id`='$sid'";
	$result=$dblink->query($sql) or
		die("<p> Something went wrong with $sql<br>".$dblink->error);
	if ($result->num_rows<=0)
		redirect("index.php?page=login&errMsg=InvalidSid");
	echo '<br><br><br><br><br><br>';
	echo '<table class="table table-bordered">';
	echo '<thead>';
	echo '<tr>';
	echo '<th>First Name</th>';
	echo '<th>Last Name</th>';
	echo '<th>Email</th>';
	echo '<th>Phone</th>';
	echo '<th>Comments</th>';
	echo '</tr>';
	echo '<thead>';
	echo '<tbody id="results">';
	echo '</tbody>';
	echo '</table>';
}
else
{
	redirect("index.php?page=login&error=NullSid");
}
?>
<script>
	function refresh_data(){
		$.ajax({
			type: 'post',
			url: 'https://ec2-3-144-182-191.us-east-2.compute.amazonaws.com/hw19/query_contacts.php',
			success: function(data){
				$('#results').html(data);
			}
		});
	}
	setInterval(function(){ refresh_data(); }, 500);
</script>