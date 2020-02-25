using UnityEngine;
using UnityEngine.UI;

public class chatHandler : MonoBehaviour
{
    [SerializeField] TCPClient client;
    [SerializeField] Text text;
    [SerializeField] InputField textField;

    //string lastLine;

    bool hasAttemptedConnecting = false;

    private void Awake()
    {
        textField.ActivateInputField();
        client.chatText[0] = "Type the IP Address we want to connect to.";
        client.chatText[1] = "If not connecting, try rebooting and type it again.";
    }

    private void FixedUpdate()
    {
        if (Input.GetKeyDown(KeyCode.Return) && hasAttemptedConnecting)
        {
            SendInputMessage();
            textField.ActivateInputField();
        }
        else if (Input.GetKeyDown(KeyCode.Return) && !hasAttemptedConnecting)
        {
            client.ConnectToServer(textField.text);
            textField.text = "";
            client.chatText[0] = "Connecting to '" + textField.text + "'...";
            client.chatText[1] = "";
            hasAttemptedConnecting = true;
            textField.ActivateInputField();
        }

        text.text = "";

        for (int i = client.chatText.Length; i > 0;)
        {
            text.text += "\n" + client.chatText[--i];
        }

        //foreach (string s in client.chatText)
        //{
        //    text.text += "\n" + s;
        //}
        //lastLine = client.chatText[0];
    }



    public void SendInputMessage()
    {
        client._SendMessage(textField.text);
        textField.text = "";
    }
}
