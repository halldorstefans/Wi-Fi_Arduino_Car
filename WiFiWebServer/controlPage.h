R"(
<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no" />
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css">
  </head>
  <body>
    <div class="container-fluid">
        <div class="col-xs-12" style="height: 100vh">
            <div class="row"
                style="height: 33.33%; padding-top: 2em; display: flex; align-items: center; justify-content: center;">
            </div>
            <div class="row" style="height: 33.33%; display: flex; align-items: center; justify-content: center;">
                <div class="col-xs-4" style="text-align: center;">
                    <button id="forward" type="button" class="btn btn-primary btn-lg">Forward</button>
                </div>
                <div class="col-xs-8"></div>
            </div>
            <div class="row"
                style="height: 33.33%; padding-bottom:2em; display: flex; align-items: center; justify-content: center;">
                <div class="col-xs-4" style="text-align: center">
                    <button id="back" type="button" class="btn btn-primary btn-lg">Back</button>
                </div>
                <div class="col-xs-4"></div>
                <div class="col-xs-2" style="text-align: center">
                    <button id="left" type="button" class="btn btn-primary btn-lg">Left</button>
                </div>
                <div class="col-xs-2" style="text-align: center">
                    <button id="right" type="button" class="btn btn-primary btn-lg">Right</button>
                </div>
            </div>
        </div>
    </div>
    <script src="https://code.jquery.com/jquery-3.6.1.min.js"></script>
    <script>
      $( "#forward" )
        .bind('touchstart mousedown', function(e){
          $.get( "/forward/", function( data ) {
          });
        })
        .bind('touchend mouseup', function(e){
          $.get( "/stop/", function( data ) {
          });
        });
      $( "#left" )
        .bind('touchstart mousedown', function(e){
          $.get( "/left/", function( data ) {
          });
        })
        .bind('touchend mouseup', function(e){
          $.get( "/straight/", function( data ) {
          });
        });
      $( "#right" )
        .bind('touchstart mousedown', function(e){
          $.get( "/right/", function( data ) {
          });
        })
        .bind('touchend mouseup', function(e){
          $.get( "/straight/", function( data ) {
          });
        });
      $( "#back" )
        .bind('touchstart mousedown', function(e){
          $.get( "/back/", function( data ) {
          });
        })
        .bind('touchend mouseup', function(e){
          $.get( "/stop/", function( data ) {
          });
        });
    </script>
  </body>
</html>
)"
