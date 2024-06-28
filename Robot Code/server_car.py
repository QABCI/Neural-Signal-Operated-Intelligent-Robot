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
    <button type="button" onclick="setValue(4)">Light off</button>  
    <button type="button" onclick="setValue(5)">Light on</button>  
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


@app.route("/")
def index():
    return render_template_string(template, current_value=current_value)


@app.route("/a", methods=["POST"])
def set_value():
    button_value = request.form.get("button", "0")
    if button_value in ["0", "1", "2", "3", "4", "5"]:
        global current_value
        global light_value
        if int(button_value) <= 3:
            current_value = int(button_value)
            light_value = light_value
        else:
            current_value = current_value
            light_value = int(button_value) - 4
    return jsonify({"status": "ok", "value": current_value})


@app.route("/s")
def get_value():
    return jsonify({"value": current_value, "light": light_value})

@app.route("/in", methods=["POST"])
def set_value_():
    value = request.json['value']
    if value in ["0", "1", "2", "3"]:
        global current_value
        global light_value
        if int(value) <= 3:
            current_value = int(value)
            light_value = light_value
    return jsonify({"status": "ok", "value": current_value})


if __name__ == "__main__":
    app.run(host="0.0.0.0", port=8976)
