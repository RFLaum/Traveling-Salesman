// This is a manifest file that'll be compiled into application.js, which will include all the files
// listed below.
//
// Any JavaScript/Coffee file within this directory, lib/assets/javascripts, vendor/assets/javascripts,
// or any plugin's vendor/assets/javascripts directory can be referenced here using a relative path.
//
// It's not advisable to add code directly here, but if you do, it'll appear at the bottom of the
// compiled file. JavaScript code in this file should be added after the last require_* statement.
//
// Read Sprockets README (https://github.com/rails/sprockets#sprockets-directives) for details
// about supported directives.
//
//= require jquery
//= require jquery_ujs
//= require_tree .

var pointHolder = [];

function clickResponse(e){
  var x = e.clientX;
  var y = e.clientY;
  pointHolder[pointHolder.length] = [x, y];
  var canvas = $('#map')[0];
  var context = canvas.getContext('2d');
  context.fillStyle = 'red';
  context.fillRect(x-3, y-3, 2, 2);
}

function makePath(arr){
  // window.alert(arr);
  var canvas = $('#map')[0];
  var context = canvas.getContext('2d');
  context.beginPath();
  context.moveTo(pointHolder[arr[0]][0],pointHolder[arr[0]][1]);

  for (var i = 1; i < arr.length; i++){
    context.lineTo(pointHolder[arr[i]][0],pointHolder[arr[i]][1]);
  }
  context.closePath();
  context.stroke();
}

function findSol(thisButton){
  var allButtons = $('button');
  allButtons.prop('disabled', true);
  thisButton.text('Calculating...');
  $.ajax({
    data: {coords: pointHolder},
    dataType: 'json',
    url: '/gene.json',
    success: function(results){
      // window.alert(results.message);
      makePath(results.winner);
      allButtons.prop('disabled', false);
      thisButton.text('Calculate');
    }
  });
}

function clearData(){
  pointHolder = [];
  $('#map')[0].getContext('2d').clearRect(0,0,500,200);
}

$(document).ready(function(){
  $('#map').on('click', clickResponse);
  $('#eraser').click(function(){
    clearData();
  });
  $('#submit').click(function(){
    findSol($(this));
  });
});
