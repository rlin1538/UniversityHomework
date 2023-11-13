package org.apache.commons.mail;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import static org.junit.Assert.*;

public class SimpleEmailTest {
    private Email email;

    @Before
    public void setUp() throws Exception {
        email = new SimpleEmail();
        email.setHostName("smtp.qq.com");
        email.setSmtpPort(465);
        email.setAuthenticator(new DefaultAuthenticator("1326612236@qq.com", "kccdtrrctnptbabe"));
        email.setSSLOnConnect(true);

        email.setMsg("这是一封简单的邮件This is a test mail ... :-)");
    }

    @After
    public void tearDown() throws Exception {
    }

    @Test
    public void setFrom() throws EmailException {
        email.setFrom("1326612236@qq.com");
        assertEquals("1326612236@qq.com",email.getFromAddress().getAddress());
    }

    @Test
    public void addTo() throws EmailException {
        email.addTo("2529039819@qq.com");
        assertEquals("2529039819@qq.com",email.getToAddresses().get(0).getAddress());
    }

    @Test
    public void setSubject() {
        email.setSubject("TestMail");
        assertEquals("TestMail",email.getSubject());
    }
}
