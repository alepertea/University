var value_array = ['0','0','1','1','2','2','3','3','4','4','5','5','6','6','7','7','8','8','9','9'];
var values = [];
var tile_ids = [];
var noTilesFlipped = 0;

Array.prototype.tile_shuffle = function()
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
	value_array.tile_shuffle();
	for (var i = 0; i < value_array.length; i++)
	{
		output += '<div id = "tile_' + i + '" onclick = "flip(this,\'' + value_array[i] + '\')"></div>';
	}
	document.getElementById('board').innerHTML = output;
}

function flip(tile, val)
{
	if (tile.innerHTML == "" && values.length < 2)
	{
		tile.style.background = "url(profi/" + val + ".jpg) no-repeat";
		tile.innerHTML = val;
		if (values.length == 0)
		{
			values.push(val);
			tile_ids.push(tile.id);
		}
		else if(values.length == 1) 
		{
			values.push(val);
			tile_ids.push(tile.id);
			if (values[0] == values[1])
			{
				noTilesFlipped += 2;
				values = [];
				tile_ids = [];
				if (noTilesFlipped == value_array.length)
				{
					alert("Contrats!");
					document.getElementById('board').innerHTML = "";
					startNewGame();		}
			}
			else
			{
				function flipBack() {
					var tile1 = document.getElementById(tile_ids[0]);
					var tile2 = document.getElementById(tile_ids[1]);
					tile1.innerHTML = "";
					tile1.style.background = "#FFFFFF"
					tile2.innerHTML = "";
					tile2.style.background = "#FFFFFF"
					values = [];
					tile_ids = [];
				}
				setTimeout(flipBack, 700);
			}
		}
	}
}