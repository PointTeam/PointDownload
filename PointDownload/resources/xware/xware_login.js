//Point.sJSLogin.connect(pointSlotLogin);
function pointSlotLogin(userName, pwd)
{
    $("#login-input-username").click();
    $("#login-input-username").val(userName);

    Point.justForJSTest("login userName: " + userName);

    $("#login-input-password").click();
    $("#login-input-password").val(pwd);

    Point.justForJSTest("login pwd: " + pwd);

    // 用于绕过验证
    Login.login.verifyCode = 1;
    $("#login-input-verify-code").val(1);
    Login.hasVerifyCode = true;

    setTimeout(
    function()
    {
        // debug
        Point.justForJSTest("login");

        $("#login-button").click();
    }, 500
    );
}
