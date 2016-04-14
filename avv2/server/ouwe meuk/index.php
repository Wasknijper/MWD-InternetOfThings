<?php  
$light = $_GET['light'];
if($light == "on") {  
  $file = fopen("lampje.txt", "w") or die("can't open file");
  fwrite($file, 'on');
  fclose($file);
} 
else if ($light == "off") {  
  $file = fopen("lampje.txt", "w") or die("can't open file");
  fwrite($file, 'off');
  fclose($file);
}
?>

<a href="?light=on">Turn On</a>  
<a href="?light=off">Turn Off</a>  
<div>  
  <?php
    if($light=="on") {
      echo("Turn LED on.");
    }
    else if ($light=="off") {
      echo("Turn LED off.");
    }
    else {
      echo ("Do something.");
    }
  ?>
</div> 