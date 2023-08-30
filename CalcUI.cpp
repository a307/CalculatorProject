#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include "CalcUI.h"
#include "BasicCalc.h"
#include "ScienceCalc.h"
#include <string>

using namespace std;

// Function to create a button
HWND CreateButton(LPCWSTR label, int x, int y, int width, int height, HWND parent, HINSTANCE hInstance, int id) {
    return CreateWindow(L"BUTTON", label, WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        x, y, width, height, parent, (HMENU)id, hInstance, NULL);
}

// Main window procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

    // create basic calculator functinoality instance
    static BasicCalc basic;

    // create science calculator functionality instance
    static ScienceCalc science;

    // create pointer of base class to toggle between
    static BasicCalc* calculate;

    // intiallity point to basic calculator
    calculate = &science; // just set to sceince and its fine?

    // current input
    static wstring input = L"";

    // current operation
    static wstring operation = L"";

    // to check if operation has been selected already
    static bool pendingEquation = false;

    // for decimals
    //static bool decimal = false;

    // science or basic mode
    static bool scienceMode = false;

    switch (msg) {
    case WM_CREATE:
        // Create text display
        textDisplay = CreateWindow(L"EDIT", L"", WS_VISIBLE | WS_CHILD | ES_RIGHT | ES_READONLY,
            10, 40, 280, 40, hwnd, NULL, ((LPCREATESTRUCT)lParam)->hInstance, NULL);

        // Create buttons

        // scientific and basic calculator toggle buttons
        CreateButton(L"Basic", 10, 10, 80, 20, hwnd, ((LPCREATESTRUCT)lParam)->hInstance, 19);
        CreateButton(L"Scientific", 100, 10, 80, 20, hwnd, ((LPCREATESTRUCT)lParam)->hInstance, 20);

        // Create basic calculator buttons

        // digits
        buttons[0] = CreateButton(L"1", 10, 90, 60, 40, hwnd, ((LPCREATESTRUCT)lParam)->hInstance, 1);
        buttons[1] = CreateButton(L"2", 80, 90, 60, 40, hwnd, ((LPCREATESTRUCT)lParam)->hInstance, 2);
        buttons[2] = CreateButton(L"3", 150, 90, 60, 40, hwnd, ((LPCREATESTRUCT)lParam)->hInstance, 3);
        buttons[3] = CreateButton(L"4", 10, 150, 60, 40, hwnd, ((LPCREATESTRUCT)lParam)->hInstance, 4);
        buttons[4] = CreateButton(L"5", 80, 150, 60, 40, hwnd, ((LPCREATESTRUCT)lParam)->hInstance, 5);
        buttons[5] = CreateButton(L"6", 150, 150, 60, 40, hwnd, ((LPCREATESTRUCT)lParam)->hInstance, 6);
        buttons[6] = CreateButton(L"7", 10, 210, 60, 40, hwnd, ((LPCREATESTRUCT)lParam)->hInstance, 7);
        buttons[7] = CreateButton(L"8", 80, 210, 60, 40, hwnd, ((LPCREATESTRUCT)lParam)->hInstance, 8);
        buttons[8] = CreateButton(L"9", 150, 210, 60, 40, hwnd, ((LPCREATESTRUCT)lParam)->hInstance, 9);
        buttons[9] = CreateButton(L"0", 80, 270, 60, 40, hwnd, ((LPCREATESTRUCT)lParam)->hInstance, 0);
        // arithmetic operations
        buttons[10] = CreateButton(L"+", 230, 90, 60, 40, hwnd, ((LPCREATESTRUCT)lParam)->hInstance, 10);
        buttons[11] = CreateButton(L"-", 230, 150, 60, 40, hwnd, ((LPCREATESTRUCT)lParam)->hInstance, 11);
        buttons[12] = CreateButton(L"*", 230, 210, 60, 40, hwnd, ((LPCREATESTRUCT)lParam)->hInstance, 12);
        buttons[13] = CreateButton(L"/", 230, 270, 60, 40, hwnd, ((LPCREATESTRUCT)lParam)->hInstance, 13);
        buttons[14] = CreateButton(L"=", 150, 270, 60, 40, hwnd, ((LPCREATESTRUCT)lParam)->hInstance, 14);
        buttons[15] = CreateButton(L"C", 10, 270, 60, 40, hwnd, ((LPCREATESTRUCT)lParam)->hInstance, 15);
        buttons[16] = CreateButton(L".", 10, 330, 60, 40, hwnd, ((LPCREATESTRUCT)lParam)->hInstance, 16);
        buttons[17] = CreateButton(L"/---", 80, 330, 60, 40, hwnd, ((LPCREATESTRUCT)lParam)->hInstance, 17); // square root
        buttons[18] = CreateButton(L"x^2", 150, 330, 60, 40, hwnd, ((LPCREATESTRUCT)lParam)->hInstance, 18); // square


        // Scientific Calculator buttons

        scienceButtons[0] = CreateButton(L"sin", 230, 330, 60, 40, hwnd, ((LPCREATESTRUCT)lParam)->hInstance, 21);
        scienceButtons[1] = CreateButton(L"cos", 10, 390, 60, 40, hwnd, ((LPCREATESTRUCT)lParam)->hInstance, 22);
        scienceButtons[2] = CreateButton(L"tan", 80, 390, 60, 40, hwnd, ((LPCREATESTRUCT)lParam)->hInstance, 23);
        scienceButtons[3] = CreateButton(L"n!", 150, 390, 60, 40, hwnd, ((LPCREATESTRUCT)lParam)->hInstance, 24);
        scienceButtons[4] = CreateButton(L"pi", 230, 390, 60, 40, hwnd, ((LPCREATESTRUCT)lParam)->hInstance, 25);
        scienceButtons[5] = CreateButton(L"x^y", 10, 450, 60, 40, hwnd, ((LPCREATESTRUCT)lParam)->hInstance, 26);
        scienceButtons[6] = CreateButton(L"e", 80, 450, 60, 40, hwnd, ((LPCREATESTRUCT)lParam)->hInstance, 27);

        // hide science buttons at start in basic mode
        for (int i = 0; i < 7; ++i) {
            ShowWindow(scienceButtons[i], SW_HIDE);
        }

        // also add log variable square root radians 10^x inverse cos and sin and tan?
        break;

    case WM_COMMAND:

        if (HIWORD(wParam) == BN_CLICKED) {
            int buttonId = LOWORD(wParam); // button click id
            switch (buttonId) {
            case 0: // Button 0 clicked (number 0)
                // add to input string 
                input += L"0";
                SendMessage(textDisplay, EM_REPLACESEL, TRUE, (LPARAM)L"0");
                break;
            case 1:
                // add to input string 
                input += L"1";
                SendMessage(textDisplay, EM_REPLACESEL, TRUE, (LPARAM)L"1");
                break;
            case 2:
                // add to input string 
                input += L"2";
                SendMessage(textDisplay, EM_REPLACESEL, TRUE, (LPARAM)L"2");
                break;
            case 3:
                // add to input string 
                input += L"3";
                SendMessage(textDisplay, EM_REPLACESEL, TRUE, (LPARAM)L"3");
                break;
            case 4:
                // add to input string 
                input += L"4";
                SendMessage(textDisplay, EM_REPLACESEL, TRUE, (LPARAM)L"4");
                break;
            case 5:
                // add to input string 
                input += L"5";
                SendMessage(textDisplay, EM_REPLACESEL, TRUE, (LPARAM)L"5");
                break;
            case 6:
                // add to input string 
                input += L"6";
                SendMessage(textDisplay, EM_REPLACESEL, TRUE, (LPARAM)L"6");
                break;
            case 7:
                // add to input string 
                input += L"7";
                SendMessage(textDisplay, EM_REPLACESEL, TRUE, (LPARAM)L"7");
                break;
            case 8:
                // add to input string 
                input += L"8";
                SendMessage(textDisplay, EM_REPLACESEL, TRUE, (LPARAM)L"8");
                break;
            case 9:
                // add to input string 
                input += L"9";
                SendMessage(textDisplay, EM_REPLACESEL, TRUE, (LPARAM)L"9");
                break;
            case 10: // addition
                if (!input.empty() && !pendingEquation) { // ensure there is a number and there is not an on-going equation

                    operation = L"+"; // set new operation

                    // store first input via mutator setResult first converting it to a double
                    calculate->setResult(stod(input));

                    //reset input for second number
                    input = L"";

                    // set pending equation to true
                    pendingEquation = true;

                    // reset decimal
                 //   decimal = false;

                    // clear display for next input
                    SendMessage(textDisplay, WM_SETTEXT, 0, (LPARAM)L"");
                }
                break;
            case 11: // subtraction
                if (!input.empty() && !pendingEquation) { // ensure there is a number and there is not an on-going equation

                    operation = L"-"; // set new operation

                    // store first input via mutator setResult first converting it to a double
                    calculate->setResult(stod(input));

                    //reset input for second number
                    input = L"";

                    // set pending equation to true
                    pendingEquation = true;

                    // reset decimal
              //      decimal = false;

                    // clear display for next input
                    SendMessage(textDisplay, WM_SETTEXT, 0, (LPARAM)L"");
                }
                break;
            case 12: // multiplication
                if (!input.empty() && !pendingEquation) { // ensure there is a number and there is not an on-going equation

                    operation = L"*"; // set new operation

                    // store first input via mutator setResult first converting it to a double
                    calculate->setResult(stod(input));

                    //reset input for second number
                    input = L"";

                    // set pending equation to true
                    pendingEquation = true;

                    // reset decimal
             //       decimal = false;

                    // clear display for next input
                    SendMessage(textDisplay, WM_SETTEXT, 0, (LPARAM)L"");
                }
                break;
            case 13: // division
                if (!input.empty() && !pendingEquation) { // ensure there is a number and there is not an on-going equation

                    operation = L"/"; // set new operation

                    // store first input via mutator setResult first converting it to a double
                    calculate->setResult(stod(input));

                    //reset input for second number
                    input = L"";

                    // set pending equation to true
                    pendingEquation = true;

                    // reset decimal
             //      decimal = false;

                    // clear display for next input
                    SendMessage(textDisplay, WM_SETTEXT, 0, (LPARAM)L"");
                }
                break;
            case 14: // equals functionality
                if (!input.empty() && !operation.empty() && pendingEquation) {
                    double num2 = stod(input); // get second input
                    double num1 = calculate->getResult(); // get first input
                    double result = 0.0;

                    // handle operations

                    if (operation == L"+") { // addition handling
                        result = calculate->add(num1, num2);
                    }
                    else if (operation == L"-") { // subtraction handling
                        result = calculate->subtract(num1, num2);
                    }
                    else if (operation == L"*") { // multiplcation handling
                        result = calculate->multiply(num1, num2);
                    }
                    else if (operation == L"/") { // division handling
                        result = calculate->divide(num1, num2);
                    }
                    else if (operation == L"x^y") { // pow x^y handling
                        calculate = &science;
                        result = calculate->opPower(num1, num2);
                    }

                    wstring resultStr = to_wstring(result);
                    SendMessage(textDisplay, WM_SETTEXT, 0, (LPARAM)resultStr.c_str()); // display result
                    input = resultStr; // store for futher use
                    operation = L""; // reset operator
                    pendingEquation = false; // reset equation status
                    //decimal = false; // reset deicmal as well
                }
                break;
            case 15: // C functionality
                //  SendMessage(textDisplay, EM_REPLACESEL, TRUE, (LPARAM)L"C");

                  // reset all fields

                input = L"";
                operation = L"";
                pendingEquation = false;
                SendMessage(textDisplay, WM_SETTEXT, 0, (LPARAM)L""); // reset display
                calculate->setResult(0.0); // reset result in basicCalc class
                // reset decimal
               // decimal = false;
                break;
            case 16: // decimal point
                if (!input.empty()) {

                    // search string for prexisting decimal point
                    if (input.find(L".") != wstring::npos) {

                        cout << "decimal already in input";

                    }
                    else {

                        input += L".";
                        SendMessage(textDisplay, EM_REPLACESEL, TRUE, (LPARAM)L".");

                        // set decimal point as true
                        //decimal = true;
                    }
                }
                break;
            case 17: // square root
                if (!input.empty()) {

                    double squareRoot_result = calculate->squareRoot(stod(input));

                    wstring squareroot_strResult = to_wstring(squareRoot_result);

                    SendMessage(textDisplay, WM_SETTEXT, 0, (LPARAM)squareroot_strResult.c_str());

                    // set input to result
                    input = squareroot_strResult;
                }
                break;
            case 18: // square
                if (!input.empty()) {

                    double square_result = calculate->square(stod(input));

                    wstring square_strResult = to_wstring(square_result);

                    SendMessage(textDisplay, WM_SETTEXT, 0, (LPARAM)square_strResult.c_str());

                    // set input to result
                    input = square_strResult;
                }
                break;
            case 19: // basic calc                

                if (scienceMode) {
                    // hide science buttons
                    for (int i = 0; i < 7; ++i) {
                        ShowWindow(scienceButtons[i], SW_HIDE);
                    }
                    calculate = &basic;
                    // reset all fields
                    input = L"";
                    operation = L"";
                    pendingEquation = false;
                    SendMessage(textDisplay, WM_SETTEXT, 0, (LPARAM)L""); // reset display
                    calculate->setResult(0.0); // reset result in basicCalc class
                    // reset decimal
                 //   decimal = false;

                    scienceMode = false;

                    calculate = &basic; // set class pointer back to basic
                }
                break;

            case 20: // science calc
                if (!scienceMode) {
                    // reveal science buttons
                    for (int i = 0; i < 7; ++i) {
                        ShowWindow(scienceButtons[i], SW_SHOW);
                    }

                    calculate = &science;

                    // reset all fields
                    input = L"";
                    operation = L"";
                    pendingEquation = false;
                    SendMessage(textDisplay, WM_SETTEXT, 0, (LPARAM)L""); // reset display
                    calculate->setResult(0.0); // reset result in science class
                    // reset decimal
               //     decimal = false;

                    scienceMode = true;

                    // calculate = &science; // now set pointer to science function
                }
                break;
                // scienctific operations
            case 21: // sin
                if (!input.empty()) {
                    calculate = &science;

                    double sin_result = calculate->sinTrig(stod(input));

                    wstring sin_strResult = to_wstring(sin_result);

                    SendMessage(textDisplay, WM_SETTEXT, 0, (LPARAM)sin_strResult.c_str());

                    // set input to result
                    input = sin_strResult;
                }
                break;
            case 22: // cos
                if (!input.empty()) {
                    calculate = &science;
                    double cos_result = calculate->cosTrig(stod(input));

                    wstring cos_strResult = to_wstring(cos_result);

                    SendMessage(textDisplay, WM_SETTEXT, 0, (LPARAM)cos_strResult.c_str());

                    // set input to result
                    input = cos_strResult;
                }
                break;
            case 23: // tan
                if (!input.empty()) {
                    calculate = &science;
                    double tan_result = calculate->tanTrig(stod(input));

                    wstring tan_strResult = to_wstring(tan_result);

                    SendMessage(textDisplay, WM_SETTEXT, 0, (LPARAM)tan_strResult.c_str());

                    // set input to result
                    input = tan_strResult;
                }
                break;
            case 24: // factorial
                if (!input.empty()) {
                    calculate = &science;
                    double factorial_result = calculate->fact(stod(input));

                    wstring factorial_strResult = to_wstring(factorial_result);

                    SendMessage(textDisplay, WM_SETTEXT, 0, (LPARAM)factorial_strResult.c_str());

                    // set input to result
                    input = factorial_strResult;
                }
                break;
            case 25: // pi
                input = L"0";
                if (!input.empty()) {
                    calculate = &science;
                    double pie_result = calculate->pie();

                    wstring pie_strResult = to_wstring(pie_result);

                    SendMessage(textDisplay, WM_SETTEXT, 0, (LPARAM)pie_strResult.c_str());

                    // set input to result
                    input = pie_strResult;

                }
                break;
            case 26: // power x^y
                if (!input.empty() && !pendingEquation) { // ensure there is a number and there is not an on-going equation
                    calculate = &science; // point to sicence calculator object
                    operation = L"x^y"; // set new operation

                    // store first input via mutator setResult first converting it to a double
                    calculate->setResult(stod(input));

                    //reset input for second number
                    input = L"";

                    // set pending equation to true
                    pendingEquation = true;

                    // reset decimal
                 //   decimal = false;

                    // clear display for next input
                    SendMessage(textDisplay, WM_SETTEXT, 0, (LPARAM)L"");
                }
                break;
            case 27: // e
                //if (!input.empty()) {
                calculate = &science;
                double e_result = calculate->e();

                wstring e_strResult = to_wstring(e_result);

                SendMessage(textDisplay, WM_SETTEXT, 0, (LPARAM)e_strResult.c_str());

                // set input to result
                input = e_strResult;
                //}
                break;

            }

        }
        break;

    case WM_DESTROY:
        // remove science buttons if basic calculaotr selected
        for (int i = 0; i < 7; ++i) {
            DestroyWindow(scienceButtons[i]);
        }

        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }

    return 0;
}

// main window function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Register the window class
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_HREDRAW | CS_VREDRAW, WndProc, 0, 0,
                      GetModuleHandle(0), LoadIcon(0, IDI_APPLICATION), LoadCursor(0, IDC_ARROW),
                      HBRUSH(COLOR_WINDOW + 1), 0, L"CalculatorClass", LoadIcon(0, IDI_APPLICATION) };
    RegisterClassEx(&wc);

    // Create the window
    hwnd = CreateWindow(L"CalculatorClass", L"Calculator", WS_OVERLAPPEDWINDOW, 100, 100, 320, 540, 0, 0, hInstance, 0);
    ShowWindow(hwnd, nCmdShow);

    // Message loop
    MSG msg;
    while (GetMessage(&msg, 0, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}
