<?php
function db_connect($db){
	$dbusername="YOUR_DB_USERNAME";
	$dbpassword="YOUR_DB_PASSWORD";
	$host="localhost";
	$dblink=new mysqli($host,$dbusername,$dbpassword,$db);
	
	return $dblink;
}

function redirect ($uri)
{ ?>
	<script type="text/javascript">
		document.location.href="<?php echo $uri; ?>";
	</script>
<?php die;
}
?>