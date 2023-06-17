<?php
include("koneksi.php");
if (!empty($_POST)) {
    $humidity = $_POST["humidity"];
    $temperature = $_POST["temperature"];
    $nilai = $_POST["nilai"];
    $query = "INSERT INTO log (humidity, temperature, nilai)
 VALUES ('" . $humidity . "', '" . $temperature . "', '" . $nilai . "')";
    if ($conn->query($query) === TRUE) {
        echo "Berhasil menyimpan data ke table log";
    } else {
        echo "Error: " . $sql . "<br>" . $conn->error;
    }
}
?>