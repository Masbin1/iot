<!DOCTYPE html>
<html>
<title>Menampilkan Data Suhu dan Kelembaban</title>
<meta name="viewport" content="width=device-width, initial-scale=1">
<link rel="stylesheet" href="https://www.w3schools.com/w3css/4/w3.css">
<body>
<div class="w3-container">
 <h1> <center>Data Hasil Pengukuran</h1>
 <h3><center>Sensor DHT11</h3>
 <table class="w3-table-all">
 <thead>
 <tr class="w3-light-blue">
 <th>NO</th>
 <th>KEGANTENGAN</th>
 <th>KEUANGAN</th>
<th>WAKTU</th>
 </tr>
 </thead>
<?php
require ("koneksi.php");
$sql="select * from log order by waktu desc";
$hasil=mysqli_query($conn,$sql);
$row=mysqli_fetch_row($hasil);
$n=1;
do
{
list($id,$suhu,$kelembaban,$waktu)=$row;
echo "<tr><td>$n</td><td>$suhu %</td><td>$kelembaban %</td><td>$waktu</td>";
$n++;
}
while($row=mysqli_fetch_row($hasil));
?> 
 </table>
</div>
</body>
</html>
