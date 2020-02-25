using UnityEngine;
using UnityEngine.UI;

public class chatHandler : MonoBehaviour
{
    [SerializeField] TCPClient client;
    [SerializeField] Text text;
    [SerializeField] InputField textField;

    //string lastLine;

    private void Awake()
    {
        textField.ActivateInputField();
    }

    private void FixedUpdate()
    {
        if (Input.GetKeyDown(KeyCode.Return))
        {
            SendInputMessage();
            textField.ActivateInputField();
        }

        text.text = "";

        for(int i = client.chatText.Length; i > 0;)
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
