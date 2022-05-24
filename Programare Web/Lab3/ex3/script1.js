var valueArray = ['0','0','1','1','2','2','3','3','4','4','5','5','6','6','7','7','8','8','9','9'];
var clickedValues = [];		// Stocam valorile pe care am dat click
var tileIDs = [];			// Stocam ID-urile tile-urilor pe care am dat click
var noTilesFlipped = 0;		// Retinem pe cate am apasat

Array.prototype.shuffle = function()
{
	for (var i = this.length - 1; i > 0; i--) 
	{
		var j = Math.floor(Math.random() * (i + 1));
		var temp = this[j];
		this[j] = this[i];
		this[i] = temp;
	}
}

function startNewGame()
{
	noTilesFlipped = 0;
	var output = '';
	valueArray.shuffle();
	for (var i = 0; i < valueArray.length; i++)
	{
		output += '<div id = "tile_' + i + '" onclick = "flip(this,\'' + valueArray[i] + '\')"></div>';
	}
	document.getElementById('board').innerHTML = output;
}

function flip(tile, val)
{
	if (tile.innerHTML == "" && clickedValues.length < 2)
	{
		tile.style.background = "#FFF";
		tile.style.fontcolor = "black";
		tile.innerHTML = val;
		if (clickedValues.length == 0)
		{
			clickedValues.push(val);
			tileIDs.push(tile.id);
		}
		else if(clickedValues.length == 1) 
		{
			clickedValues.push(val);
			tileIDs.push(tile.id);
			if (clickedValues[0] == clickedValues[1])
			{
				noTilesFlipped += 2;
				document.getElementById(tileIDs[0]).style.backgroundColor = "green";
				document.getElementById(tileIDs[1]).style.backgroundColor = "green";
				clickedValues = [];
				tileIDs = [];
				if (noTilesFlipped == valueArray.length)
				{
					alert("Contrats!");
					document.getElementById('board').innerHTML = "";
					startNewGame();
				}
			}
			else
			{
				function flipBack() {
					var tile1 = document.getElementById(tileIDs[0]).innerHTML = "";
					var tile2 = document.getElementById(tileIDs[1]).innerHTML = "";
					clickedValues = [];
					tileIDs = [];
				}
				setTimeout(flipBack, 700);
			}
		}
	}
}