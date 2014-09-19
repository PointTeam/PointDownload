//Point.sJSLogin.connect(pointSlotLogin);

var spliterBtwData = "#..#";
var spliterEnd = "#.^_^.#";

var pointLoginCheckInterval;
var pointLoginCheckHandle;

function pointSlotLogin(userName, pwd, vertifyCode)
{
    $("#login-input-username").click();
    $("#login-input-username").val(userName);
    $("#login-input-password").click();
    $("#login-input-password").val(pwd);

    $("#login-input-verify-code").val(vertifyCode);

    pointLoginCheckHandle = false;
    pointLoginCheckInterval = setInterval("pointLoginCheckSlot()", 500);


    // 用于绕过验证
//    Login.login.verifyCode = 1;
//    $("#login-input-verify-code").val(1);
//    Login.hasVerifyCode = true;

    setTimeout(
    function()
    {
        // debug
        Point.justForJSTest("login");

        $("#login-button").click();
    }, 500
    );
}

function pointLoginCheckSlot()
{
    if(pointLoginCheckHandle === false)
    {
        if($("#login-account-username-error-box").css("display") === "block")
        {
            Point.loginError(1, $("#login-account-username-error-msg").html());
            pointLoginCheckHandle = true;
        }

        if($("#login-account-password-error-box").css("display") === "block")
        {
            Point.loginError(2, $("#login-account-password-error-msg").html());
            pointLoginCheckHandle = true;
        }

        if($("#login-verify-code-error-box").css("display") === "block")
        {
            Point.loginError(3, $("#login-verify-code-error-msg").html() + spliterBtwData
                             + $("#verify-code-image").attr("src"));
            pointLoginCheckHandle = true;
        }

        // is any wrong handled
        if(pointLoginCheckHandle)
        {
            window.clearInterval(pointLoginCheckInterval);
        }
    }
}



