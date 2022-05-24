function sort(index) 
{
	var elements, x, y, shouldSwitch, switchCount = 0;
	var table = document.getElementById("table");
	var switching = true;
	var sortDirection = "ASC";
	  
	while (switching) 
	{
		switching = false;
		elements = table.getElementsByTagName("tr");
		for (var i = 1; i < elements.length - 1; i++) 
		{
			shouldSwitch = false;
			x = elements[i].getElementsByTagName("td")[index];
			y = elements[i + 1].getElementsByTagName("td")[index];
			if (sortDirection == "ASC") {
				if (x.innerHTML.toLowerCase() > y.innerHTML.toLowerCase()) 
				{
					shouldSwitch = true;
					break;
				}
			} 
			else if (sortDirection == "DESC") 
			{
				if (x.innerHTML.toLowerCase() < y.innerHTML.toLowerCase()) 
				{
					shouldSwitch = true;
					break;
				}
			}
		}
		if (shouldSwitch) 
		{
			elements[i].parentNode.insertBefore(elements[i + 1], elements[i]);
			switching = true;
			switchCount++;
		} 
		else
		{
			if (switchCount == 0 && sortDirection == "ASC")
			{
				sortDirection = "DESC";
				switching = true;
			}
		}
	}
}
