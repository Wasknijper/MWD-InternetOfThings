<?php

$file = 'lampje.txt';
$value = file_get_contents($file);

if($value == 1){
	$message = 'Lampje is aan!';
} else {
	$message = 'Lampje is uit!';
}

if(isset($_POST['on']))
{
        $previous = file_get_contents($file);
        file_put_contents($file, '1');
        $message = 'Lampje is aan!';
    }

if(isset($_POST['off']))
{
        $previous = file_get_contents($file);
        file_put_contents($file, '0');
        $message = 'Lampje is uit!';
    }
?> 

<html>
	<body> 
		<h1> LED there be light! </h1>   
		<form action="" method="post">
			<?php echo $message; ?>
			<input type="submit" name="on" value="On" />
			<input type="submit" name="off" value="Off" />
		</form>    
	</body>
</html>