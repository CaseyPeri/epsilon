#ifndef ESCHER_TEXT_FIELD_H
#define ESCHER_TEXT_FIELD_H

#include <escher/scrollable_view.h>
#include <escher/text_field_delegate.h>
#include <escher/text_cursor_view.h>
#include <string.h>

class TextField : public ScrollableView, public ScrollViewDataSource {
public:
  TextField(Responder * parentResponder, char * textBuffer, char * draftTextBuffer, size_t textBufferSize,
    TextFieldDelegate * delegate = nullptr, bool hasTwoBuffers = true, KDText::FontSize size = KDText::FontSize::Large, float horizontalAlignment = 0.0f,
    float verticalAlignment = 0.5f, KDColor textColor = KDColorBlack, KDColor = KDColorWhite);
  void setDelegate(TextFieldDelegate * delegate);
  void setDraftTextBuffer(char * draftTextBuffer);
  Toolbox * toolbox() override;
  bool isEditing() const;
  const char * text() const;
  int textLength() const;
  int cursorLocation() const;
  void setText(const char * text);
  void setBackgroundColor(KDColor backgroundColor);
  KDColor backgroundColor() const;
  void setTextColor(KDColor textColor);
  void setAlignment(float horizontalAlignment, float verticalAlignment);
  virtual void setEditing(bool isEditing, bool reinitDraftBuffer = true);
  void setCursorLocation(int location);
  /* If the text to be appended is too long to be added without overflowing the
   * buffer, nothing is done (not even adding few letters from the text to reach
   * the maximum buffer capacity) and false is returned. */
  bool insertTextAtLocation(const char * text, int location);
  KDSize minimalSizeForOptimalDisplay() const override;
  bool handleEvent(Ion::Events::Event event) override;
  bool textFieldShouldFinishEditing(Ion::Events::Event event);
  constexpr static int maxBufferSize() {
     return ContentView::k_maxBufferSize;
  }
protected:
  class ContentView : public View {
  public:
    ContentView(char * textBuffer, char * draftTextBuffer, size_t textBufferSize, KDText::FontSize size, float horizontalAlignment = 0.0f,
    float verticalAlignment = 0.5f, KDColor textColor = KDColorBlack, KDColor = KDColorWhite);
    void setDraftTextBuffer(char * draftTextBuffer);
    void drawRect(KDContext * ctx, KDRect rect) const override;
    void reload();
    bool isEditing() const;
    const char * text() const;
    int textLength() const;
    int cursorLocation() const;
    char * textBuffer();
    char * draftTextBuffer();
    int bufferSize();
    void setText(const char * text);
    void setBackgroundColor(KDColor backgroundColor);
    KDColor backgroundColor() const;
    void setTextColor(KDColor textColor);
    void setAlignment(float horizontalAlignment, float verticalAlignment);
    void setEditing(bool isEditing, bool reinitDraftBuffer);
    void reinitDraftTextBuffer();
    void setCursorLocation(int location);
    bool insertTextAtLocation(const char * text, int location);
    KDSize minimalSizeForOptimalDisplay() const override;
    KDCoordinate textHeight() const;
    KDCoordinate charWidth();
    void deleteCharPrecedingCursor();
    bool deleteEndOfLine();
    KDRect cursorRect();
    View * subviewAtIndex(int index) override;
    /* In some app (ie Calculation), text fields record expression results whose
     * lengths can reach 70 (ie
     * [[1.234567e-123*e^(1.234567e-123*i), 1.234567e-123*e^(1.234567e-123*i)]]).
     * In order to be able to record those output text, k_maxBufferSize must be
     * over 70. */
    constexpr static int k_maxBufferSize = 100;
  private:
    int numberOfSubviews() const override;
    void layoutSubviews() override;
    TextCursorView m_cursorView;
    bool m_isEditing;
    char * m_textBuffer;
    char * m_draftTextBuffer;
    size_t m_currentTextLength;
    size_t m_currentCursorLocation;
    size_t m_textBufferSize;
    float m_horizontalAlignment;
    float m_verticalAlignment;
    KDColor m_textColor;
    KDColor m_backgroundColor;
    KDText::FontSize m_fontSize;
  };
  ContentView m_contentView;
private:
  void deleteCharPrecedingCursor();
  bool deleteEndOfLine();
  void scrollToCursor();
  bool m_hasTwoBuffers;
  TextFieldDelegate * m_delegate;
};

#endif
