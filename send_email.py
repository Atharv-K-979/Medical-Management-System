import sys
import smtplib
import ssl
from email.message import EmailMessage

def main():
    if len(sys.argv) < 4:
        print("Usage: python send_email.py \"message\" \"subject\" email1 [email2 ...]")
        sys.exit(1)

    message = sys.argv[1]
    subject = sys.argv[2]
    recipients = sys.argv[3:]

    sender_email = "tonystark03042003@gmail.com"
    app_password = "vxfr unyg wtrs qmut"  # Gmail App Password (not regular password)

    msg = EmailMessage()
    msg.set_content(message)
    msg['Subject'] = subject
    msg['From'] = sender_email
    msg['To'] = ", ".join(recipients)

    context = ssl.create_default_context()

    try:
        with smtplib.SMTP_SSL('smtp.gmail.com', 465, context=context) as server:
            server.login(sender_email, app_password)
            server.send_message(msg)
        print("✅ Email sent successfully.")
    except smtplib.SMTPAuthenticationError:
        print("❌ Authentication failed. Check app password.")
    except Exception as e:
        print(f"❌ Failed to send email: {e}")

if __name__ == "__main__":
    main()
