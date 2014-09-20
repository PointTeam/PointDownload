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

pointVertifyChangeIntervalId = setInterval("pointVertifyCodeCheckSlot()", 200);

var vertifyCodeLink = "/img/wh.png";
function pointVertifyCodeCheckSlot()
{
//    Point.justForJSTest("pointVertifyCodeCheckSlot" + $("#verify-code-image").attr("src"));
    var vertifyCodeLinkTmp = $("#verify-code-image").attr("src");
    if(vertifyCodeLink != vertifyCodeLinkTmp
            && vertifyCodeLinkTmp != "/img/wh.png"
        && vertifyCodeLinkTmp != "")
    {
        vertifyCodeLink = vertifyCodeLinkTmp;
        var msg = $("#login-verify-code-error-msg").html();
        if(msg != "" && Login.isLogining !== 1)
        {
            Point.loginError(3, msg + spliterBtwData + vertifyCodeLink);
        }
    }
}

function pointUpdateVertifyCode()
{
    $("#verify-code-image").click();
//    pointSlotLogin($("#login-input-username").val(), $("#login-input-password").val())
}



