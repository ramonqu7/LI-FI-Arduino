# LI-FI-Arduino

## Please check the paper vlc_paper.pdf
<object data="vlc_paper.pdf" type="application/pdf" width="700px" height="700px">
    <embed src="vlc_paper.pdf">
        This browser does not support PDFs. Please download the PDF to view it: <a href="vlc_paper.pdf">Download PDF</a>.</p>
    </embed>
</object>
### If you have any question please send email to quramon@gmail.com, Thanks

Wireless communications, such as Wi-Fi and Bluetooth, are commonly used in the daily life. However, while more and more wireless devices occupy the available frequencies, the frequency spectrum is reaching a maximum capacity.

Thus, Li-Fi, communicating using light waves between two devices, becomes a future solution to transmit data. LED devices with a data wave generator may keep the lighting functionality of a LED while sending data in the background. With the full range of the visible and infrared light spectrum, we may transmit data day and night. With Li-Fi, data communication happens indoors with low latency and high speed and is hard to hijack from outside the room. On the receiver side, a small solar panel both receives the signal and recycles the power to charge the battery for future use. It thus saves energy lost in standard wireless data transmission. The system consists of two Arduino (microcontroller) devices as the emitter and receiver. The user interface, based on the Python programming language, is used to control sending and receiving data. Infrared LED signals the beginning and end of the data transmission During the transmission, LEDs switching on and off signal binary 0’s and 1’s.

This system can transmit text and images successfully. However, with the limitation of the consumer-grade solar panel’s response time, it is hard to reach high speeds in data transmission. With high-end and low-response-time components, it will be able to transmit live videos at high speeds. The Li-Fi system not only provides the basic lighting function but also sends the data and power to the receiver side.
## ----------------------------
## Usage
- pypic -
Python end for receiver side.
Pypic.py is reeiver Side

- transmitter
Python for transmitter(emitter side)

- re_calib
Arduino Code for Light threathold calibration.

- re_data
Arduino code for Light Receiver side

- tran
Arduino code for Light Emitter side

- tr/transmitter1
Arduino code for Light Emitter side testing
