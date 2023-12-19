<?php
//Creates new record as per request
    //Connect to database
    $servername = "localhost";
    $username = "root";
    $password = "";
    $dbname = "demo";
    try {
        // Création de la connection à la base de donnée
        $conn = new PDO("mysql:host=localhost;dbname=demo",$username,$password);
        // Attribution de pa ramètres à PDO pour afficher des erreurs 
        $conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
        
        if(isset($_GET["temperature"])){ // vérifie si le paramètre temperature est dans l’URL pour pouvoir exécuter le code suivant 
        print($_GET["temperature"]);
        print($_GET["humidite"]);
        print($_GET["presence"]);
        print($_GET["distance"]);
        
        $requete = "INSERT INTO logs (temperature, humidite, presence, distance) VALUES (:temperature, :humidite, :presence, :distance)";
        $stmt= $conn->prepare($requete); // Préparation de la requête 
        // Attribution des variables aux paramètres de la requête
        $stmt->bindParam(':temperature', $_GET["temperature"]);
        $stmt->bindParam(':humidite', $_GET["humidite"]);
        $stmt->bindParam(':presence', $_GET["presence"]);  
        $stmt->bindParam(':distance', $_GET["distance"]);  
        // Exécution de la requête avec ces paramètres 
        $stmt->execute(); 
        
        }
        } catch(PDOException $e) { // Affiche une erreur si la connection a échoué
         echo "connexion echoue".$e->getMessage();
        }
?>