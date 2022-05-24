$('#firstList').dblclick(function()
			{
				return !$('#firstList option:selected').remove().appendTo('#secondList');
			});
$('#secondList').dblclick(function() 
			{
				return !$('#secondList option:selected').remove().appendTo('#firstList');
			});