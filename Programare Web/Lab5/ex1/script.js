function getStations() {
	var source = $("source");
	var destination = $("destination");
	var sourceCity = source.options[source.selectedIndex].value;
	
	var request = new XMLHttpRequest();
	request.onreadystatechange = function() {
		if (request.readyState == 4) {
			if (request.status == 200){
				destination.html('');
				var array = eval('(' + request.responseText + ')');
				for (var i = 0; i < array.length; i++) {
					var option = document.createElement('option');
					option.text = array[i];
					option.value = array[i];
					destination.add(option, null);
				}
			}
			else {
				alert('request.status error: ' + request.status);
			}
		}
	}
	
	request.open('GET', 'getDestinations.php?source=' + sourceCity);
	request.send('');
}

