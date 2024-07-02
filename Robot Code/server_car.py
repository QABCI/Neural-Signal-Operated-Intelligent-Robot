from flask import Flask, render_template_string, request, jsonify

app = Flask(__name__)
current_value = 0
light_value = 0

template = """  
<!doctype html>  
<title>Button Test</title>  
<h1>Choose a number</h1>  
<script src="https://code.jquery.com/jquery-3.6.0.min.js"></script>  
<form id="number-form" method="post">  
    <button type="button" onclick="setValue(0)">0</button>  
    <button type="button" onclick="setValue(1)">1</button>  
    <button type="button" onclick="setValue(2)">2</button>  
    <button type="button" onclick="setValue(3)">3</button>  
</form>  
<p>Current Value: <span id="current-value">{{ current_value }}</span></p>  
  
<script>  
function setValue(value) {  
    $.ajax({  
        url: '/a',  
        type: 'POST',  
        data: { button: value },  
        success: function(response) {  
            $('#current-value').text(response.value);  
        },  
        error: function(error) {  
            console.error('Error:', error);  
        }  
    });  
}  
</script>  
"""


@app.route("/") #debug page to control the car
def index():
    return render_template_string(template, current_value=current_value)


@app.route("/a", methods=["POST"]) #the place to update value
def set_value():
    button_value = request.form.get("button", "0")
    if button_value in ["0", "1", "2", "3", "4", "5"]:
        global current_value
        if int(button_value) <= 3:
            current_value = int(button_value)
        else:
            current_value = current_value
    return jsonify({"status": "ok", "value": current_value})


@app.route("/s")    #get value from arduino
def get_value():
    return jsonify({"value": current_value, "light": light_value})  #the light value is useless now



if __name__ == "__main__":
    app.run(host="0.0.0.0", port=8976)
