var key = config.API_KEY;
var city = "London";
var url = "api.openweathermap.org/data/2.5/weather?q=" + city + "&appid=" + key;

var app = {
    load: function() {
        this.getData();
    },
    getData: function() {
       $.ajax({
           url: url,
           type: 'GET',
           dataType: 'jsonp',
           error: function(err) {
               console.log("something is wrong");
               console.log(err);
           },
           success: function(data) {
                console.log(data);
           }
       });
    }
};
app.load();