<?php
//Creates new record as per request
    //Connect to database
    $servername = "localhost";
    $username = "root";
    $password = "";
    $dbname = "demo";

    // Create connection
    $conn = new mysqli($servername, $username, $password, $dbname);
    // Check connection
    if ($conn->connect_error) {
        die("Database Connection failed: " . $conn->connect_error);
    }

    //Get current date and time
    date_default_timezone_set('Europe/France');
    $d = date("Y-m-d");
    //echo " Date:".$d."<BR>";
    $t = date("H:i:s");

    if(!empty($_GET['temperature']) && !empty($_GET['humidite']) && !empty($_GET['presence']) && !empty($_GET['distance']))
    {
    	$temperature = $_GET['temperature'];
    	$humidite = $_GET['humidite'];
        $presence = $_GET['presence'];
        $distance = $_GET['distance'];

	    $sql = "INSERT INTO logs (temperature, humidite, presence, distance, Date, Time)
		
		VALUES ('".$temperature."', '".$humidite."', '".$presence."', '".$distance."', '".$d."', '".$t."')";

		if ($conn->query($sql) === TRUE) {
		    echo "OK";
		} else {
		    echo "Error: " . $sql . "<br>" . $conn->error;
		}
	}


	$conn->close();
?>