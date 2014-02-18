var start = 0;
var end = 4;

function handleMessage(message_event){
	console.log(message_event.data);
	$('#output').text(message_event.data);
}

function moduleDidLoad(){
	console.log("geladen");
}

function sendCommand(command, para){
	module = document.getElementById('star');

	if(typeof para!='undefined'){
		var jsonOb = {"command": command, nodes: para};
	}else{
		var jsonOb = {"command": command};
	}
	jsonOb = jQuery.stringify(jsonOb);
	console.log(jsonOb);
	module.postMessage(jsonOb);
}

function reloadTextArea(){
	//lade alles in textare
	toSend = Array();
	$('#connections > li').each(function(index){
		tmp = $(this).text();
		tmp = tmp.split(',');
		for (i = 0; i < tmp.length; ++i) {
			tmp[i] = parseInt(tmp[i]);
		}
		toSend.push(tmp);
	});
	$('#textArea').val(jQuery.stringify(toSend));
}

$(document).ready(function() {	
	var listener = document.getElementById('listener');
	listener.addEventListener('load', moduleDidLoad, true);
	listener.addEventListener('message', handleMessage, true);

	reloadTextArea();

	$('#submitt').click(function(event) {
		event.preventDefault();
		var tmp = jQuery.parseJSON($('#textArea').val());

		var i = 0;
		$('#connections > li').each(function(index) {
			var text = "";
			for(j = 0; j < tmp[i].length; ++j){				
				if(j != 0){
					text +=', ';
				}
				text += tmp[i][j];
			}
			$(this).text(text);
			++i;
		});
	});

	$('#sendToNative').click(function(event) {
		event.preventDefault();
		var toSend = Array();
		$('#nodes > li').each(function(index){
			tmp = $(this).text();
			tmp = tmp.split(',');
			toSend.push({"x": parseInt(tmp[0]), "y": parseInt(tmp[1])});
		});
		
		sendCommand("setNodes", toSend);

		toSend = Array();
		$('#connections > li').each(function(index){
			tmp = $(this).text();
			tmp = tmp.split(',');
			for (i = 0; i < tmp.length; ++i) {
				tmp[i] = parseInt(tmp[i]);
			}
			toSend.push(tmp);
		});

		sendCommand("setConnections", toSend);

		sendCommand("solve", Array(start, end));
	});

	$('#resetNodes').click(function(event) {
		event.preventDefault();
		sendCommand("resetNodes");
	});

	$('#resetConnections').click(function(event) {
		event.preventDefault();
		sendCommand("resetConnections");
	});

	$('#submitAdd').click(function(event) {
		event.preventDefault();
		val = $('#cord').val();
		$('#nodes').append('<li>' + val + '</li>');
		val = $('#conn').val();
		$('#connections').append('<li>' + val + '</li>');

		reloadTextArea();
	});

	$('#setStartEnd').click(function(event) {
		event.preventDefault();
		startEnd = $('#startEnd').val();
		tmp = startEnd.split(',');
		start = parseInt(tmp[0]);
		end = parseInt(tmp[1]);
	});

});
