<?php
if(isset($_POST['on']))
{
        $file = 'lampje.txt';
        $previous = file_get_contents($file);
        file_put_contents($file, '1');

    }
?>

<?php
if(isset($_POST['off']))
{
        $file = 'lampje.txt';
        $previous = file_get_contents($file);
        file_put_contents($file, '0');

    }
?> 

<html>
	<body>    
		<form action="" method="post">
			<?php echo $message; ?>
			<input type="submit" name="on" value="On" />
			<input type="submit" name="off" value="Off" />
		</form>    
	</body>
</html>