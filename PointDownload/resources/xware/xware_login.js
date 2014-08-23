Point.sLogin.connect(pointSlotLogin);
//function pointSlotLogin(userName, pwd)
//{
//    $("#login-input-username").click();
//    $("#login-input-username").val(userName);
//    $("#login-input-password").click();
//    $("#login-input-password").val(pwd);

//    // 用于绕过验证
//    Login.login.verifyCode = 1;
//    $("#login-input-verify-code").val(1);
//    Login.hasVerifyCode = true;

//    var pointIntervalId_tmp = setInterval(
//    function ()
//    {
//        if(window.location != "http://yuancheng.xunlei.com/3/")
//        {
//            // debug
//             Point.justForJSTest("login");

//            $("#login-button").click();
//        }
//    }
//    , 1000);
//}

function pointSlotLogin(userName, pwd)
{
    $("#login-input-username").click();
    $("#login-input-username").val(userName);
    $("#login-input-password").click();
    $("#login-input-password").val(pwd);

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
