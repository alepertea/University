var valueArray = ['0','0','1','1','2','2','3','3','4','4','5','5','6','6','7','7','8','8','9','9'];
var clickedValues = [];
var tileIDs = [];
var noTilesFlipped = 0;

Array.prototype.tileShuffle = function()
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
	valueArray.tileShuffle();
	for (var i = 0; i < valueArray.length; i++)
	{
		output += '<div id = "tile_' + i + '" onclick = "flip(this,\'' + valueArray[i] + '\')"></div>';
	}
	//document.getElementById("board").innerHTML = output;
	$('#board').html(output);
}

function flip(tile, val)
{
	if (tile.innerHTML == '' && clickedValues.length < 2)
	{
		tile.style.background = 'url(profi/' + val + '.jpg) no-repeat';
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
				clickedValues = [];
				tileIDs = [];
				if (noTilesFlipped == valueArray.length)
				{
					alert('Congrats!');
					//document.getElementById("board").innerHTML = "";
					$('#board').html('');
					startNewGame();		
				}
			}
			else
			{
				function flipBack() 
				{
					var tile1 = $('#' + tileIDs[0]);
					var tile2 = $('#' + tileIDs[1]);
					//var tile1 = document.getElementById(tile_ids[0]);
					//var tile2 = document.getElementById(tile_ids[1]);
					tile1.html('');
					tile1.css('background', 'white');
					tile2.html('');
					tile2.css('background', 'white');
					//tile1.innerHTML = '';
					//tile1.style.background = 'white';
					//tile2.innerHTML = '';
					//tile2.style.background = 'white';
					clickedValues = [];
					tileIDs = [];
				}
				setTimeout(flipBack, 700);
			}
		}
	}
}