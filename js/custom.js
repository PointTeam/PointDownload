var matchNavigationButtons = 1;


/* don't edit anything below here unless you're very certain of what you're doing */


function triBackHome() {

	pos = $('#navigation ul li a.current').position();
	
	if(pos) {
		$("#triSlideContainer img").stop().animate({marginLeft:(pos.left+(widest/2+10))+"px"}, 1000);
	} else {
		$("#triSlideContainer img").css("display", "none");
	}
	
}

$(window).load(function () {
  	
  	triBackHome();
  	
  	//activate testimonial slides (only if it's part of the DOM)
	if($('#testimonials')[0]) {
		$('#testimonials').cycle({ 
    		speed:	2000,
    		timeout: 7000, 
    		delay:  0
   		});
   	}
   	
   	//put some events on the search field
   	
   	$('#search input').focus(function(){ $(this).stop().animate({backgroundColor: "#fdf5e8"}, 1000); $(this).css("borderColor", "#f89d1c") })
	
	$('#search input').blur(function(){ $(this).stop().animate({backgroundColor: "#fffff"}, 1000); $(this).css("borderColor", "#527cae") });
  	
});

timer = "";

var widest = 0;

jQuery(document).ready(function(){

	//connect event for QSM drop down

	$('#qsm').click(function(){toggleQSM()});
	

	//set initial position for the little yellow triangle
	
	pos = $('#navigation ul li a.current').position();
	
	if(!pos) {
		$("#triSlideContainer img").css("display", "none");
	}
	
	
	//connect main navigation events
	$('#navigation ul li a').mousedown(function(){$(this).addClass('current')});
	
	$('#navigation ul li a').mouseup(function(){$(this).removeClass('current')});
	

	//set the same width for each button in the navigation, use the width of the widest button
	
	if(matchNavigationButtons == 1) {
		
		butts = $('#navigation ul li a span')
	
		butts.each(function(){
		
			currentWidth = $(this).width();
 		 		 		
 			if(currentWidth > widest) {
 			
 				widest  = currentWidth; 
 			
 			}		
		});
	
		$('#navigation ul li a span').css("width", widest+"px")
	
	}
	

	$('#qsmContainer').css('display', 'none');
	$('#qsmContainer').css('visibility', 'visible');
   	
	$('#navigation ul li a').bind("mouseenter", function(e){
					
		//we'll move the little yellow triangle to the button over which the mouse
		//is hovering
				
		pos = $(this).position();
								
		$("#triSlideContainer img").stop().animate({marginLeft:(pos.left+(widest/2+10))+"px"}, 1000, "swing");
		
	});
	
	$('#navigation ul li a').bind("mouseleave", function(e){
		
		triBackHome();
			
	});
	
})

function toggleQSM() {
	
	$('#qsmContainer').toggle('slide', {direction:"up"}, 1000, function(){
				
		if($('#down').css("display") == 'inline') {
		
			$('#down').css("display", "none");
			$('#up').css("display", "inline");
			
			$('#qsmContainer').css('zIndex', 100);
		
		} else {
		
			$('#down').css("display", "inline");
			$('#up').css("display", "none");
		
		}
		
	});
}

