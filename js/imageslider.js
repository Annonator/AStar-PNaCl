(function($){
	$.fn.imageSlider = function( _options ) {
		var options = $.extend({
				displayDuration: 5000,
				animationDuration: 1200,
				animation: 'fade',
				appearance: 'in',
				easing: 'swing',
				delimiter: '|'
			}, _options==undefined ? {} : _options),
			container = $(this),
			width = container.width(),
			height = container.height(),
			nav = $('<ul/>'),
			timer = null,
			slides = null,
			current = null,
			next = null,
			animations = null,
			currentAnimation = 0;
		setTimer = function() {
			if( timer )
				window.clearTimeout(timer);
			timer = window.setTimeout(function(){
				var next = nav.find('.current').closest('li').next();
				if( next.length==0 )
					next = nav.find('li:first');
				next.find('a').trigger('click');
			},options.displayDuration);
		}
		if( $.isArray(options.animation) ) {
			animations = options.animation;
			options.animation = animations[currentAnimation];
		}
		container.find('a').each(function(i){
			var img = $(this).find('img').detach(),
				title = img.attr('title'),
				subtitle = '',
				delimiterPosition = title!=undefined ? title.indexOf(options.delimiter) : -1;
			if( delimiterPosition>0 ) {
				subtitle = $.trim(title.substr(delimiterPosition+1));
				title = $.trim(title.substr(0,delimiterPosition));
			}
			else
				title = $.trim(title);
			$(this).html('<em>'+title+'</em>').wrap('<div/>').after(img);
			if( subtitle!='' )
				$(this).append('<span>'+subtitle+'</span>');
			img.attr('title','');
			nav.append(
				$('<li/>').append(
					$('<a href="#" title="'+title+'"></a>').click(function(ev){
						ev.preventDefault();
						if( slides.filter(':animated').length>0 || slides.filter(':eq('+i+')').is(':visible') )
							return;
						var aniOptions = {
							easing: options.easing,
							duration: options.animationDuration,
							complete: function() {
								current.hide()
								setTimer();
							}
						};
						nav.find('.current').removeClass('current');
						$(this).blur().addClass('current');
						if( options.appearance=='out' ) {
							current = slides.filter(':visible').css('z-index',2);
							next = slides.filter(':eq('+i+')').css({
								'z-index':1,
								top:0,
								left:0,
								opacity:1
							}).show();
						}
						else {
							current = slides.filter(':visible').css('z-index',1);
							next = slides.filter(':eq('+i+')').css('z-index',2);
						}
						switch( options.animation ) {
							case 'top right':
							case 'right top':
								if( options.appearance=='out' )
									current.animate({top:-height,left:width},aniOptions);
								else
									next.css({top:-height,left:width}).show().animate({top:0,left:0},aniOptions);
								break;
							case 'top left':
							case 'left top':
								if( options.appearance=='out' )
									current.animate({top:-height,left:-width},aniOptions);
								else
									next.css({top:-height,left:-width}).show().animate({top:0,left:0},aniOptions);
								break;
							case 'bottom left':
							case 'left bottom':
								if( options.appearance=='out' )
									current.animate({top:height,left:-width},aniOptions);
								else
									next.css({top:height,left:-width}).show().animate({top:0,left:0},aniOptions);
								break;
							case 'bottom right':
							case 'right bottom':
								if( options.appearance=='out' )
									current.animate({top:height,left:width},aniOptions);
								else
									next.css({top:height,left:width}).show().animate({top:0,left:0},aniOptions);
								break;
							case 'top':
								if( options.appearance=='out' )
									current.animate({top:-height},aniOptions);
								else
									next.css('top',-height).show().animate({top:0},aniOptions);
								break;
							case 'bottom':
								if( options.appearance=='out' )
									current.animate({top:height},aniOptions);
								else
									next.css('top',height).show().animate({top:0},aniOptions);
								break;
							case 'left':
								if( options.appearance=='out' )
									current.animate({left:-width},aniOptions);
								else
									next.css('left',-width).show().animate({left:0},aniOptions);
								break;
							case 'right':
								if( options.appearance=='out' )
									current.animate({left:width},aniOptions);
								else
									next.css('left',width).show().animate({left:0},aniOptions);
								break;
							case 'fade':
							default:
								if( options.appearance=='out' )
									current.animate({opacity:0},aniOptions);
								else
									next.css('opacity',0).show().animate({opacity:1},aniOptions);
								break;
						}
						if( animations ) {
							currentAnimation = currentAnimation<(animations.length-1) ? currentAnimation+1 : 0;
							options.animation = animations[ currentAnimation ];
						}
					}).addClass( i==0 ? 'current' : '' )
				)
			);
		});
		slides = $(this).find('div');
		slides.not(':first').hide();
		$(this).append(nav);
		setTimer();
		return $(this);
	}
})(jQuery)