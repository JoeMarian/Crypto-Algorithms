from flask import Flask, request, jsonify, send_from_directory
import subprocess
import os

app = Flask(__name__, static_folder='.', static_url_path='')

@app.route('/')
def serve_index():
    return send_from_directory('.', 'index.html')

@app.route('/run', methods=['POST'])
def run_cipher():
    cipher = request.form['cipher']
    mode = request.form['mode'].upper()
    message = request.form['message']
    key = request.form['key']

    executable = f"./{cipher}_cipher"

    if not os.path.exists(executable):
        return jsonify(output=f"Error: {executable} not found. Make sure the C file is compiled.")

    # Construct the input string for the C program
    input_data = f"{mode}\n{message}\n{key}\n"

    try:
        result = subprocess.run(
            [executable],
            input=input_data,
            capture_output=True,
            text=True,
            timeout=5
        )
        return jsonify(output=result.stdout)
    except Exception as e:
        return jsonify(output=f"Error running the cipher: {str(e)}")

if __name__ == '__main__':
    app.run(debug=True)
