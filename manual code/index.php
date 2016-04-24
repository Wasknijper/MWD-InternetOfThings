<?php  
    if(isset($_POST["servo"])){
        $file = fopen("servo.txt", "w") or die("can't open file");
        fwrite($file, $_POST["servo"]);
        fclose($file);
    }

    if ($_SERVER["REQUEST_METHOD"] === "POST") {
      // Waarde wegschrijven naar bestand
      $data = $_POST["pir"];

      // Push data to text file
      $timestamp = new DateTime();
      $time = $timestamp->format('Y-m-d H:i:s');
      // $message = array("Time: " => .$timestamp->format('Y-m-d H:i:s'). , " pir: " => .$data.);
      $message = array("time" => $time, "pir" => $data);
        $inp = file_get_contents('movement.json');
        $tempArray = json_decode($inp);
        array_push($tempArray, $message);
        $jsonData = json_encode($tempArray);
        file_put_contents('movement.json', $jsonData);
      // file_put_contents("output.txt", print_r($message, true) . "\n", FILE_APPEND);
    }
?>

<html>
    <head>
        <style>
            body {
                background-color: #2c3e50;
                background-image: url(tux.jpg);
                background-size: cover;
                display: flex;
                justify-content: center;
                align-items: center;
                flex-wrap: wrap;
                padding: 3em 0;
            }

            #activity{
                background-color: white;
                margin: 0 auto;
            }

            h1, h2 {
                font-family: "Lato";
                color: white;
                width: 100vw;
                text-align: center;
            }

            h2 {
                width: auto;
            }
            .off, .on {
                border: none;
                border-bottom: 5px solid #ecf0f1;
                width: 10em;
                font-family: "Lato";
                font-size: 2em;
                background-color: white;
                border-radius: 10px;
                padding: .5em;
            }
            
            .on, .aOn {
                color: #2ecc71;
            }
            .off, .aOff {
                color: #e74c3c;
            }
            
            .on:focus {
                border-bottom: none;
                transform: translateY(5px);
            }
            .off:focus {
                border-bottom: none;
                transform: translateY(5px);
            }
            a {
                text-decoration: none;
            }
            .turn {
                font-family: 'Lato';
                color: white;
                width: 100%;
                text-align: center;
            }
            button {
                margin: .4em .2em;
                cursor: pointer;
            }
            .history {
                color: white;
                border-bottom: 3px solid white;
                font-size: 1.3em;
                padding-bottom: .2em;
                transition: all ease 100ms;
            }
            .history:hover {
                border-bottom: 5px solid white;                
            }
           
            a {
                color: white;
            }
            form {
                text-align: center;
            }
        </style>
    </head>
    <body>


    <h1>Play with Tux</h1>
    <div class="turn">  
        Toy is at <?php echo($_POST["servo"]); ?> degrees!
    </div> 
    <form action="" method="POST">
        <label><h2>Control the toy!</h2></label>
        <input type="range" min="0" max="180" value=<?php echo($_POST["servo"]); ?> id="slider" name="servo" onchange=/>
        <br />
        <input type=submit value=Submit />
    </form>
    <div class="turn">
        Tux status: <span id="status"></span>
    </div>
    

    <script src="https://code.jquery.com/jquery-1.12.3.min.js"></script>
    <script>
        $.getJSON( "movement.json", function( data) {
            console.log(data);
            var status = $(data).last();
            console.log(status[0].pir);   

            if(status === 0) {
                $('#status').html('sleeping');
            } else {
                $('#status').html('active');
            }
        });
    </script>
    </body>
</html>