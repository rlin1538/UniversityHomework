import org.apache.commons.mail.*;

public class TestEmail {
    public static void main(String[] args) throws EmailException {
        //实例化email对象
        Email email = new SimpleEmail();
        //配置基本信息
        email.setHostName("smtp.qq.com");
        email.setSmtpPort(465);
        email.setAuthenticator(new DefaultAuthenticator("1326612236@qq.com", "kccdtrrctnptbabe"));
        email.setSSLOnConnect(true);

        //测试setFrom方法
        email.setFrom("1326612236@qq.com");
        if (!email.getFromAddress().getAddress().equals("1326612236@qq.com"))
            System.out.println("setFrom()函数未通过测试: 结果应该是‘1326612236@qq.com’，但返回了"+email.getFromAddress().getAddress());
        //测试setSubject方法
        email.setSubject("TestMail");
        if (!email.getSubject().equals("TestMail"))
            System.out.println("setSubject()函数未通过测试: 结果应该是‘TestMail’，但返回了"+email.getSubject());
        //测试setMsg方法
        email.setMsg("这是一封简单的邮件This is a test mail ... :-)");
        //测试addTo方法
        email.addTo("2529039819@qq.com");
        if (!email.getToAddresses().get(0).getAddress().equals("2529039819@qq.com"))
            System.out.println("addTo()函数未通过测试: 结果应该是‘2529039819@qq.com’，但返回了"+email.getToAddresses().get(0).getAddress());
        //email.send();
    }
}
