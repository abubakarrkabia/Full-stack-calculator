let currentInput = "";
let currentOperator = "";
let firstNumber = null;

function appendNumber(num) {
    currentInput += num;
    document.getElementById("display").value = currentInput;
}

function setOperator(op) {
    if (currentInput !== "") {
        firstNumber = currentInput;
        currentInput = "";
        currentOperator = op;
    }
}

function clearDisplay() {
    currentInput = "";
    firstNumber = null;
    currentOperator = "";
    document.getElementById("display").value = "";
}

async function calculate() {
    if (firstNumber !== null && currentInput !== "") {
        const response = await fetch(`http://localhost:8080/calculate?a=${firstNumber}&b=${currentInput}&op=${currentOperator}`);
        const result = await response.text();
        document.getElementById("display").value = result;
        firstNumber = null;
        currentInput = result;
    }
}
