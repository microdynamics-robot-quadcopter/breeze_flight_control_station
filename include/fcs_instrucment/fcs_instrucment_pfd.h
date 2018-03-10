#ifndef FCS_INSTRUCMENT_PFD_H
#define FCS_INSTRUCMENT_PFD_H

#include <QGraphicsView>
#include <QGraphicsSvgItem>

class FCSInstrucmentPFD : public QGraphicsView
{
    Q_OBJECT

    // Altimeter pressure units.
    enum PressureUnit
    {
        STD, // Standard (displays STD instead of numerical value).
        MB,  // Milibars.
        IN   // Inches of mercury.
    };

public:
    explicit FCSInstrucmentPFD(QWidget *parent = 0);
    ~FCSInstrucmentPFD();
    void reinitPFD(void);
    void updatePFD(void);
    inline void setPFDRollAngle(float roll_angle) {}
    inline void setPFDPitchAngle(float pitch_angle) {}
    inline void setPFDPathMarker(float attack_angle, float sideslip_angle,
                                 bool visible = true)
    {

    }
    inline void setPFDSlipSkid(float slip_skid) {}
    inline void setPFDTurnRate(float turn_rate) {}
    inline void setPFDBarHorizontal(float bar, bool visible = true) {}
    inline void setPFDBarVertical(float bar, bool visible = true) {}
    inline void setPFDDotHorizontal(float dot, bool visible = true) {}
    inline void setPFDDotVertical(float dot, book visible = true) {}
    inline void setPFDAltitude(float altitude) {}
    inline void setPFDPressure(float pressure, PressureUnit unit) {}
    inline void setPFDAirspeed(float airspeed) {}
    inline void setPFDMachNumber(float mach_number) {}
    inline void setPFDHeading(float heading) {}
    inline void setPFDClimbRate(float climb_rate) {}
protected:
    void resizeEvent(QResizeEvent *event);
private:
    class PanelADI
    {
    public:
        PanelADI(QGraphicsScene *scene);
        ~PanelADI();
        void initADI(float scale_x, float scale_y);
        void updateADI(float scale_x, float scale_y);
        void setADIRollAngle(float roll_angle);
        void setADIPitchAngle(float pitch_angle);
        void setADIFlightPathMarker(float attack_angle, float sideslip_angle,
                                    bool visible = true );
        void setADISlipSkid(float slip_skid);
        void setADITurnRate(float turn_rate);
        void setADIBarHorizontal(float bar, bool visible = true);
        void setADIBarVertical(float bar, bool visible = true);
        void setADIDotHorizontal(float dot, bool visible = true);
        void setADIDotVertical(float dot, bool visible = true);
    private:
        void resetADI(void);
        void updateADILadd(float delta, float roll_sin, float roll_cos);
        void updateADILaddBack(float delta, float roll_sin, float roll_cos);
        void updateADIRollAngle(void);
        void updateSlipSkip(float roll_sin, float roll_cos);
        void updateADITurnRate(void);
        void updateADIFlightPath(void);
        void updateADIBars(void);
        void updateADIDots(void);
    private:
        QGraphicsScene    *pfd_scene_;
        QGraphicsSvgItem  *pfd_item_back_;
        QGraphicsSvgItem  *pfd_item_ladd_;
        QGraphicsSvgItem  *pfd_item_roll_;
        QGraphicsSvgItem  *pfd_item_slip_;
        QGraphicsSvgItem  *pfd_item_turn_;
        QGraphicsSvgItem  *pfd_item_path_;
        QGraphicsSvgItem  *pfd_item_mark_;
        QGraphicsSvgItem  *pfd_item_bar_h_;
        QGraphicsSvgItem  *pfd_item_bar_v_;
        QGraphicsSvgItem  *pfd_item_dot_h_;
        QGraphicsSvgItem  *pfd_item_dot_v_;
        QGraphicsSvgItem  *pfd_item_mask_;
        QGraphicsSvgItem  *pfd_item_scale_h_;
        QGraphicsSvgItem  *pfd_item_scale_v_;
        // PFD variables.
        float pfd_angle_roll_;
        float pfd_angle_pitch_;
        float pfd_angle_attack_;
        float pfd_angle_sideslip_;
        float pfd_slip_skid_;
        float pfd_turn_rate_;
        float pfd_bar_h_;
        float pfd_bar_v_;
        float pfd_dot_h_;
        float pfd_dot_v_;
        // PFD visible variables.
        bool pfd_path_valid_;
        bool pfd_path_visible_;
        bool pfd_bar_h_visible_;
        bool pfd_bar_v_visible_;
        bool pfd_dot_h_visible_;
        bool pfd_dot_v_visible_;
        // PFD delta variables.
        float pfd_ladd_delta_x_new_;
        float pfd_ladd_delta_x_old_;
        float pfd_ladd_back_delta_x_new_;
        float pfd_ladd_back_delta_x_old_;
        float pfd_ladd_back_delta_y_new_;
        float pfd_ladd_back_delta_y_old_;
        float pfd_ladd_delta_y_new_;
        float pfd_ladd_delta_y_old_;
        float pfd_slip_delta_x_new_;
        float pfd_slip_delta_x_old_;
        float pfd_slip_delta_y_new_;
        float pfd_slip_delta_y_old_;
        float pfd_turn_delta_x_new_;
        float pfd_turn_delta_x_old_;
        float pfd_path_delta_x_new_;
        float pfd_path_delta_x_old_;
        float pfd_path_delta_y_new_;
        float pfd_path_delta_y_old_;
        float pfd_mark_delta_x_new_;
        float pfd_mark_delta_x_old_;
        float pfd_mark_delta_y_new_;
        float pfd_mark_delta_y_old_;
        float pfd_bar_h_delta_x_new_;
        float pfd_bar_h_delta_x_old_;
        float pfd_bar_v_delta_y_new_;
        float pfd_bar_v_delta_y_old_;
        float pfd_dot_h_delta_x_new_;
        float pfd_dot_h_delta_x_old_;
        float pfd_dot_v_delta_y_new_;
        float pfd_dot_v_delta_y_old_;
        float pfd_scale_x_;
        float pfd_scale_y_;
        // PFD deflection variables.
        const float pfd_original_pix_per_deg_;
        const float pfd_delta_ladd_back_max_;
        const float pfd_delta_ladd_back_min_;
        const float pfd_max_slip_deflection_;
        const float pfd_max_turn_deflection_;
        const float pfd_max_bars_deflection_;
        const float pfd_max_dots_deflection_;
        // PFD original variables.
        QPointF pfd_original_adi_ctr_;
        QPointF pfd_original_back_pos_;
        QPointF pfd_original_ladd_pos_;
        QPointF pfd_original_roll_pos_;
        QPointF pfd_original_slip_pos_;
        QPointF pfd_original_turn_pos_;
        QPointF pfd_original_path_pos_;
        QPointF pfd_original_bar_h_pos_;
        QPointF pfd_original_bar_v_pos_;
        QPointF pfd_original_dot_h_pos_;
        QPointF pfd_original_dot_v_pos_;
        QPointF pfd_original_scale_h_pos_;
        QPointF pfd_original_scale_v_pos_;
        // PFD z axis variables.
        const int pfd_back_z_;
        const int pfd_ladd_z_;
        const int pfd_roll_z_;
        const int pfd_slip_z_;
        const int pfd_path_z_;
        const int pfd_bars_z_;
        const int pfd_dots_z_;
        const int pfd_scales_z_;
        const int pfd_mask_z_;
        const int pfd_turn_z_;
    };

    class PanelALT
    {
    public:
        PanelALT(QGraphicsScene *scene);
        ~PanelALT();
        void initALT(float scale_x, float scale_y);
        void updateALT(float scale_x, float scale_y);
        void setALTAltitude(float altitude);
        void setALTPressure(float pressure, int unit);
    private:
        void resetALT(void);
        void updateALTAltitude(void);
        void updateALTPressure(void);
        void updateALTScale(void);
        void updateALTScaleLabels(void);
    private:
        QGraphicsScene    *alt_scene_;
        QGraphicsSvgItem  *alt_item_back_;
        QGraphicsSvgItem  *alt_item_scale1_;
        QGraphicsSvgItem  *alt_item_scale2_;
        QGraphicsTextItem *alt_item_label1_;
        QGraphicsTextItem *alt_item_label2_;
        QGraphicsTextItem *alt_item_label3_;
        QGraphicsSvgItem  *alt_item_ground_;
        QGraphicsSvgItem  *alt_item_frame_;
        QGraphicsTextItem *alt_item_altitude_;
        QGraphicsTextItem *alt_item_pressure_;
        // ALT color variables.
        QColor alt_frame_text_color_;
        QColor alt_press_text_color_;
        QColor alt_labels_color_;
        // ALT font variables.
        QFont  alt_frame_text_font_;
        QFont  alt_labels_font_;
        // ALT float variables.
        float alt_altitude_;
        float alt_pressure_;
        // ALT pressure unit.
        int alt_pressure_unit_;
        // ALT delta variables.
        float alt_scale1_delta_y_new_;
        float alt_scale1_delta_y_old_;
        float alt_scale2_delta_y_new_;
        float alt_scale2_delta_y_old_;
        float alt_ground_delta_y_new_;
        float alt_ground_delta_y_old_;
        float alt_labels_delta_y_new_;
        float alt_labels_delta_y_old_;
        // ALT scale variables.
        float alt_scale_x_;
        float alt_scale_y_;
        // ALT original float variables.
        const float alt_original_pix_per_alt_;
        const float alt_original_scale_height_;
        const float alt_original_labels_x_;
        const float alt_original_label1_y_;
        const float alt_original_label2_y_;
        const float alt_original_label3_y_;
        // ALT original QPointF variables.
        QPointF alt_original_back_pos_;
        QPointF alt_original_scale1_pos_;
        QPointF alt_original_scale2_pos_;
        QPointF alt_original_ground_pos_;
        QPointF alt_original_frame_pos_;
        QPointF alt_original_altitude_ctr_;
        QPointF alt_original_pressure_ctr_;
        // ALT z axis variables.
        const int alt_back_z_;
        const int alt_scale_z_;
        const int alt_labels_z_;
        const int alt_ground_z_;
        const int alt_frame_z_;
        const int alt_frame_text_z_;
    };

    class PanelASI
    {
    public:
        PanelASI(QGraphicsScene *scene);
        ~PanelASI();
        void intASI(float scale_x, float scale_y);
        void updateASI(float scale_x, float scale_y);
        void setASIAirspeed(float airspeed);
        void setASIMachNumber(float mach_number);
    private:
        void resetASI(void);
        void updateASIAirspeed(void);
        void updateASIScale(void);
        void updateASIScaleLabels(void);
    private:
        QGraphicsScene    *asi_scene_;
        QGraphicsSvgItem  *asi_item_back_;
        QGraphicsSvgItem  *asi_item_scale1_;
        QGraphicsSvgItem  *asi_item_scale2_;
        QGraphicsTextItem *asi_item_label1_;
        QGraphicsTextItem *asi_item_label2_;
        QGraphicsTextItem *asi_item_label3_;
        QGraphicsTextItem *asi_item_label4_;
        QGraphicsTextItem *asi_item_label5_;
        QGraphicsTextItem *asi_item_label6_;
        QGraphicsTextItem *asi_item_label7_;
        QGraphicsSvgItem  *asi_item_frame_;
        QGraphicsTextItem *asi_item_airspeed_;
        QGraphicsTextItem *asi_item_mach_number_;
        // ASI color variables.
        QColor asi_frame_text_color_;
        QColor asi_labels_color_;
        // ASI font variables.
        QFont  asi_frame_text_font_;
        QFont  asi_labels_font_;
        // ASI float variables.
        float asi_airspeed_;
        float asi_mach_number_;
        // ASI delta variables.
        float asi_scale1_delta_y_new_;
        float asi_scale1_delta_y_old_;
        float asi_scale2_delta_y_new_;
        float asi_scale2_delta_y_old_;
        float asi_labels_delta_y_new_;
        float asi_labels_delta_y_old_;
        // ASI scale variables.
        float asi_scale_x_;
        float asi_scale_y_;
        // ASI original float variables.
        const float asi_original_pix_rer_spd_;
        const float asi_original_scale_height_;
        const float asi_original_labels_x_;
        const float asi_original_label1_y_;
        const float asi_original_label2_y_;
        const float asi_original_label3_y_;
        const float asi_original_label4_y_;
        const float asi_original_label5_y_;
        const float asi_original_label6_y_;
        const float asi_original_label7_y_;
        // ASI original QPointF variables.
        QPointF asi_original_back_pos_;
        QPointF asi_original_scale1_pos_;
        QPointF asi_original_scale2_pos_;
        QPointF asi_original_frame_pos_;
        QPointF asi_original_airspeed_ctr_;
        QPointF asi_original_mach_number_ctr_;
        // ASI z axis variables.
        const int asi_back_z_;
        const int asi_scale_z_;
        const int asi_labels_z_;
        const int asi_frame_z_;
        const int asi_frame_text_z_;
    };

    class PanelHSI
    {
    public:
        PanelHSI(QGraphicsScene *scene);
        ~PanelHSI();
        void initHSI(float scale_x, float scale_y);
        void updateHSI(float scale_x, flaot scale_y);
        void setHSIHeading(float heading);
    private:
        void resetHSI(void);
        void updateHeading(void);
    private:
        QGraphicsScene    *hsi_scene_;
        QGraphicsSvgItem  *hsi_item_back_;
        QGraphicsSvgItem  *hsi_item_face_;
        QGraphicsSvgItem  *hsi_item_marks_;
        QGraphicsTextItem *hsi_item_frame_text_;
        // HSI color variable.
        QColor hsi_frame_text_color_;
        // HSI font variable.
        QFont  hsi_frame_text_font_;
        // HSI heading variable.
        float hsi_heading_;
        // HSI scale variables.
        float hsi_scale_x_;
        float hsi_scale_y_;
        // HSI original variables.
        QPointF m_original_hsi_ctr_;
        QPointF m_original_back_pos_;
        QPointF m_original_face_pos_;
        QPointF m_original_marks_pos_;
        QPointF m_original_frame_text_ctr_;
        // HSI z axis variables.
        const int m_back_z_;
        const int m_face_z_;
        const int m_marks_z_;
        const int m_frame_text_z_;
    };

    class PanelVSI
    {
    public:
        PanelVSI(QGraphicsScene *scene);
        ~PanelVSI();
        void initVSI(float scale_x, float scale_y);
        void updateVSI(float scale_x, float scale_y);
        void setVSIClimbRate(float climb_rate);
    private:
        void resetVSI(void);
        void updateVSI(void);
    private:
        QGraphicsScene    *vsi_scene_;
        QGraphicsSvgItem  *vsi_item_scale_;
        QGraphicsSvgItem  *vsi_item_arrow_;
        // VSI climb rate.
        float vsi_climb_rate_;
        // VSI delta variables.
        float vsi_arrow_delta_y_new_;
        float vsi_arrow_delta_y_old_;
        // VSI scale variables.
        float vsi_scale_x_;
        float vsi_scale_y_;
        // VSI original float variables.
        const float vsi_original_marke_height_;
        const float vsi_original_pix_per_spd1_;
        const float vsi_original_pix_per_spd2_;
        const float vsi_original_pix_per_spd4_;
        // VSI original QPointF variables.
        QPointF vsi_original_scale_pos_;
        QPointF vsi_original_arrow_pos_;
        // VSI z axis variables.
        const int vsi_scale_z_;
        const int vsi_arrow_z_;
    };
private:
    void initPFD(void);
    void resetPFD(void);
    void updatePFDView(void);
private:
    QGraphicsScene *pfd_scene_;
    PanelADI       *pfd_panel_adi_;
    PanelALT       *pfd_panel_alt_;
    PanelASI       *pfd_panel_asi_;
    PanelHSI       *pfd_panel_hsi_;
    PanelVSI       *pfd_panel_vsi_;
    // PFD svg items
    QGraphicsSvgItem *pfd_item_back_;
    QGraphicsSvgItem *pfd_item_mask_;
    // PFD scale variables.
    float pfd_scale_x_;
    float pfd_scale_y_;
    // PFD original variables.
    const int pfd_original_height_;
    const int pfd_original_width_;
    // PFD z axis variables.
    const int pfd_back_z_;
    const int pfd_mask_z_;
};

#endif // FCS_INSTRUCMENT_PFD_H
