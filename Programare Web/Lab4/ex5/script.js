var slideIndex = 1;
showSlides(slideIndex);

function changeSlide(n) 
{
	slideIndex += n;
	showSlides(slideIndex);
}

function showSlides(n) 
{
	var i;
	var slides = $('.slide');
	if (n > slides.length) 
	{
		slideIndex = 1;
	}
	if (n < 1) 
	{
		slideIndex = slides.length;
	}
	for (i = 0; i < slides.length; i++)
	{
		slides[i].css('display', 'none');
	}
	slides[slideIndex - 1].css('display', 'block');
	setTimeout(2000, showSlides);
}