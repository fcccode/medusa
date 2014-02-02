#ifndef __MEDUSA_LABEL_HPP__
#define __MEDUSA_LABEL_HPP__

#include "medusa/namespace.hpp"
#include "medusa/address.hpp"
#include "medusa/export.hpp"
#include "medusa/types.hpp"

#include <string>
#include <cstring>
#include <memory>

#ifdef _MSC_VER
# pragma warning(disable: 4251)
#endif

MEDUSA_NAMESPACE_BEGIN

//! Label is a string associated with an Address.
class Medusa_EXPORT Label
{
public:
  enum Type
  {
    Unknown       = 0x0000, //! Undefined type.
    Code          = 0x0001, //! This label contains code.
    Function      = 0x0002, //! This label contains a function
    Data          = 0x0003, //! This label contains data.
    String        = 0x0004, //! This label contains a string.
    CellMask      = 0x000f,
    Imported      = 0x0010, //! This label is imported.
    Exported      = 0x0020, //! This label is exported.
    Global        = 0x0030, //! This label is global.
    Local         = 0x0040, //! This label is local.
    AccessMask    = 0x00f0,
    AutoGenerated = 0x0100, //! This label is auto-generated
  };

  Label(Address const& rAddress, u16 Type = Unknown);
  Label(std::string const& rName = "", u16 Type = Unknown);
  ~Label(void);

  std::string Dump(void) const;

  std::string GetName(void) const { return m_spName.get(); }
  u16         GetType(void) const { return m_Type; }
  void        SetType(u16 Type) { m_Type = Type; }
  std::string GetLabel(void) const;

  void IncrementVersion(void);

  bool IsAutoGenerated(void) const;

  bool operator<(Label const& rLabel) const;
  bool operator==(Label const& rLabel) const;
  bool operator!=(Label const& rLabel) const
  {
    return !(*this == rLabel);
  }

protected:
  static char ConvertToLabel(char c);

  std::shared_ptr<char> m_spName;
  u16                   m_NameLength;
  u16                   m_Type;
  u32                   m_Version;
};

MEDUSA_NAMESPACE_END

#endif // !__MEDUSA_LABEL_HPP__