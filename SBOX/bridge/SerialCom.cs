using System.IO.Ports;
using TMPro;
using UnityEngine;
using System.Threading;

public class SerialCom : MonoBehaviour
{
    SerialPort mySerialPort;
    string receivedData;
    bool isRunning = true;

    // 확인용
    public TMP_Text mpuTxt, triggerTxt;
    int idx = 0;

    // 처리용
    private bool trigger = false;
    private Vector2 point = Vector2.zero;

    void Start()
    {
        //mySerialPort = new SerialPort("/dev/ttyS2", 115200); // Linux 용
        mySerialPort = new SerialPort("COM13", 115200); // Windows 용
        mySerialPort.ReadTimeout = 1000; // 읽기 타임아웃 설정
        try
        {
            mySerialPort.Open();  // 시리얼 포트 열기
            Debug.Log("Open success\n");
            //triggerTxt.text = "Open success";
            new Thread(Run).Start();
        }
        catch (System.Exception ex)
        {
            Debug.Log("Error opening serial port: " + ex.Message);
            //triggerTxt.text = "Error opening serial port";
        }
    }

    //void Update()
    //{
    //    if (trigger)
    //    {
    //        triggerTxt.text = "trigger clicked" + idx;
    //        trigger = false;
    //    }
    //    mpuTxt.text = "{" + point.x + ", " + point.y + "}";
    //}

    public bool GetTrigger() => trigger;
    public Vector2 GetPoint() => point;

    void Run()
    {
        while (isRunning)
        {
            if (mySerialPort != null && mySerialPort.IsOpen && mySerialPort.BytesToRead > 0)
            {
                receivedData = mySerialPort.ReadLine();
                Debug.Log(receivedData);
                if (receivedData.StartsWith("trigger"))
                {
                    trigger = true;
                    idx++;
                }
                else if (receivedData.StartsWith("point"))
                {
                    // point,{x},{y},{z}
                    string[] tmp = receivedData.Split(",");
                    point.Set(float.Parse(tmp[1]), float.Parse(tmp[3]));
                }
            }
        }
    }

    void OnDestroy()
    {
        isRunning = false;
        if (mySerialPort != null && mySerialPort.IsOpen)
        {
            mySerialPort.Close();  // 시리얼 포트 닫기
        }
    }
}
