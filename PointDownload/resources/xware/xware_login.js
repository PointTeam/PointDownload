//Point.sJSLogin.connect(pointSlotLogin);

var spliterBtwData = "#..#";
var spliterEnd = "#.^_^.#";

var pointLoginCheckInterval;
var pointLoginCheckHandle;  // record the login warning check state

var pointVertifyChangeIntervalId;

// login frame
$p_lf = $("#loginIframe").contents();

function pointSlotLogin(userName, pwd, vertifyCode)
{
    $p_lf.find("#al_c").val(vertifyCode);
    $p_lf.find("#al_u").val(userName);
    $p_lf.find("#al_p").val(pwd);
    $p_lf.find("#al_c").val(vertifyCode);

    pointLoginCheckHandle = false;
    pointLoginCheckInterval = setInterval("pointLoginCheckSlot()", 800);

    setTimeout(
    function()
    {
        // debug
        Point.justForJSTest("login");

        $p_lf.find("#al_submit").get(0).click();
    }, 500
    );
}

// check login even (pwd incorrect, username not exist ...)
function pointLoginCheckSlot()
{
    if(pointLoginCheckHandle === false)
    {
        if($p_lf.find("#al_warn").css("display") === "block")
        {
            Point.loginError(1, $p_lf.find("#al_warn").html());
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
var lastVc = ""
function pointVertifyCodeCheckSlot()
{
    var vc = $p_lf.find("#al_c_img").attr("src")
    if(vc !== lastVc)
    {
        Point.justForJSTest("pointVertifyCodeCheckSlot: " + vc)
        Point.loginError(2,  vc);
        lastVc = vc;
    }
}

function pointUpdateVertifyCode()
{
    $p_lf.find("#al_c_img").click();
}



