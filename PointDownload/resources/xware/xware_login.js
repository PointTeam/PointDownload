//Point.sJSLogin.connect(pointSlotLogin);

var spliterBtwData = "#..#";
var spliterEnd = "#.^_^.#";

var pointLoginCheckInterval;
var pointLoginCheckHandle;

var pointVertifyChangeIntervalId;

function pointSlotLogin(userName, pwd, vertifyCode)
{
    $("#login-input-username").click();
    $("#login-input-username").val(userName);
    $("#login-input-password").click();
    $("#login-input-password").val(pwd);

    $("#login-input-verify-code").val(vertifyCode);

    pointLoginCheckHandle = false;
    pointLoginCheckInterval = setInterval("pointLoginCheckSlot()", 500);
    pointVertifyChangeIntervalId = setInterval("pointVertifyCodeCheckSlot()", 500);

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

var vertifyCodeLink = "/img/wh.png";
function pointVertifyCodeCheckSlot()
{
    if(vertifyCodeLink !== $("#verify-code-image").attr("src") && $("#verify-code-image").attr("src") != "/img/wh.png")
    {
        vertifyCodeLink = $("#verify-code-image").attr("src");

        if($("#login-verify-code-error-box").css("display") === "block")
        {
            Point.loginError(3, $("#login-verify-code-error-msg").html() + spliterBtwData
                             + $("#verify-code-image").attr("src"));
            pointLoginCheckHandle = true;
        }
    }
}

function pointUpdateVertifyCode()
{
    $("#login-account-password-error-msg").click();
    pointSlotLogin($("#login-input-username").val(), $("#login-input-password").val())
}



