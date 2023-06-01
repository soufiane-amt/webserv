<!DOCTYPE html>
<html>
<head>
    <title>Greeting</title>
</head>
<body>
    <?php
    if ($_SERVER["REQUEST_METHOD"] == "POST") {
        $name = $_POST["name"];
        echo "<h1>Hello, $name!</h1>";
    }
    ?>
</body>
</html>
