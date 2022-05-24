function One_to_Two()
{
    var firstList = document.getElementById("firstList");
    var secondList = document.getElementById("secondList");
    var selectedIndex = firstList.selectedIndex;
    var element = document.createElement("option");
	
    element.text = firstList[selectedIndex].value;
    secondList.add(element);
    firstList.remove(selectedIndex);
}

function Two_to_One()
{
	var firstList = document.getElementById("firstList");
    var secondList = document.getElementById("secondList");
    var selectedIndex = secondList.selectedIndex;
    var element = document.createElement("option");
	
    element.text = secondList[selectedIndex].value;
    firstList.add(element);
    secondList.remove(selectedIndex);
}

$("firstList").ondblclick(function(){
	var firstList = $("firstList").element;
	var secondList = $("secondList").element;
	var selectedIndex = firstList.selectedIndex;
    var element = $("document").createElement("option");
	
	element.text = firstList[selectedIndex].value;
    secondList.add(element);
    firstList.remove(selectedIndex);
})