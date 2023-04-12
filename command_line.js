<!DOCTYPE html>
<html>
<head>
	<title>Bar and Button</title>
</head>
<body>
	<form>
		<label for="input">Type Something:</label>
		<input type="text" id="input">
		<button type="submit" onclick="sendData()">Send</button>
	</form>
	<div id="bar"></div>

	<script>
        
		function sendData() {
			// Get the value from the input field
			var input = document.getElementById("input").value;
            
			// Do something with the input value
			// For this example, we'll just display it in the bar
			var bar = document.getElementById("bar");
			bar.innerHTML = input;
			print(input);
		}
	</script>
</body>
</html>
